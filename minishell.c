#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <signal.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>

#include "internals.h"
#include "execute.h"
#include "jobs.h"
#include "minishell_input.h"

void tratar_zombie() {
    int statusChild = 0;
    pid_t pid;

	// Recogemos el pid del proceso que finaliza en
	// en segundo plano, y se lo pasamos a la función
	// jobs_finished por parametro.
    do{
		pid = waitpid((pid_t)(-1), &statusChild, WNOHANG); 	
		if(pid > 0){
			jobs_finished(pid);
		}
    }while(pid > 0);
    return;
}

int main (int argc, char *argv[])
{
    char buf[BUFSIZ];
    char *token;

    // Manejador de señal.
    signal(SIGCHLD, tratar_zombie);

    /*
    2ª forma de hacerlo:
    	struct sigaction sig;
    	sig.sa_handler = tratar_zombie;
    	sig.sa_flags = SA_RESTART;
    	sigaction(SIGCHLD, &sig, NULL);
    */

    while(1){
		print_prompt();
		read_command_line(buf);
		token = strtok(buf, ";");

		while(token != NULL){
			if((strcmp(token, "exit") == 0 )){
				jobs_free_mem();
				exit(0);
			}else if(is_internal_command(token)){
				execute_internal_command(token);
			}else {
				execute_external_command(token);
			}
			token = strtok(NULL, ";");
		}
    }
    return 0;
}

