#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include "process_manager.h"

pid_t launch_process(char *program, char **args)
{
    pid_t pid = fork();

    if(pid < 0)
    {
        perror("Error: fork() failed");
        return -1;
    }

    if(pid == 0)
    {
        execvp(program, args);

        perror("Error: execvp() failed");
        _exit(1);
    }

    return pid;
}