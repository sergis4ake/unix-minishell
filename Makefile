CFLAGS = -Wall
OBJETOS = minishell.o minishell_input.o execute.o free_args.o
FUENTES = minishell.c minishell_input.c execute.c free_args.c
LIB = ./lib/Linux/x86_64/libshell.a
CC = gcc

minishell: $(OBJETOS) $(LIB)
	$(CC) $(OBJETOS) $(CFLAGS) $(LIB) -o minishell

minishell.o: minishell.c minishell_input.h
	$(CC) $(CFLAGS) -c minishell.c

minishell_input.o: minishell_input.c minishell_input.h
	$(CC) $(CFLAGS) -c minishell_input.c

execute.o: execute.c execute.h
	$(CC) $(CFLAGS) -c execute.c

free_args.o: free_args.c free_args.h
	$(CC) $(CFLAGS) -c free_args.c

.PHONY: clean
clean:
	$(RM) $(OBJETOS) minishell
