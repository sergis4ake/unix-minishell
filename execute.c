#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

#include "parser.h"
#include "execute.h"
#include "free_args.h"
#include "jobs.h"

void execute_external_command(const char *command)
{
    char **args;
    int backgr = 0;
    pid_t pid;
    int statusChild = 0;

    // Si no existe ningun comando en el proceso hijo. 
    // La funcion parser_command almacena en un array el comando insertado.
    // Ademas almacena en &backgr si el comando contiene (1) o no (0) el caracter "&" .
    if ((args=parser_command(command, &backgr)) == NULL){ 
        return;
    }

    // Crea el proceso hijo.
    pid=fork();

    if(pid==-1){
	    perror("\nError al ejecutar fork().\n");
	    return;
    // Proceso hijo.
    }else if(pid == 0){
        if((execvp(*args, args))==-1){ // Ejecuta el comando pasado por parámetros.
            perror("\nError al ejecutar el comando externo.\n");
            exit(-1);
        }
    // Proceso padre.
    }else if(pid > 0){
        jobs_new(pid, *args);
        if(backgr==0){
            // Espera por el proceso, si no existe '&'.
            pid = wait(&statusChild);
            // Sobrescribe la finalización de los procesos hijos que se ejecutan en 1º plano.
            jobs_finished(pid);
	    }

        // Liberar memoria del array creado en parser_command.
        parser_free_args(args);
    }
    return;
}
