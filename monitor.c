#include <stdio.h>
#include <sys/wait.h>
#include <signal.h>
#include <string.h>
#include "monitor.h"

void monitor_process(pid_t pid, char *program)
{
    int status;

    if(waitpid(pid, &status, 0) < 0)
    {
        perror("Error: waitpid() failed");
        return;
    }

    printf("\n--- Sandbox Execution Report ---\n");
    printf("Program : %s\n", program);
    printf("PID     : %d\n", pid);

    if(WIFEXITED(status))
    {
        printf("Result  : Program exited normally\n");
        printf("Exit Code : %d\n", WEXITSTATUS(status));
    }

    else if(WIFSIGNALED(status))
    {
        int sig = WTERMSIG(status);

        printf("Result  : ");

        switch(sig)
        {
            case SIGXCPU:
                printf("CPU time limit exceeded (SIGXCPU)\n");
                break;

            case SIGSEGV:
                printf("Segmentation Fault (SIGSEGV)\n");
                break;

            case SIGKILL:
                printf("Process killed (SIGKILL)\n");
                break;

            case SIGABRT:
                printf("Program aborted (SIGABRT)\n");
                break;

            case SIGFPE:
                printf("Arithmetic exception (SIGFPE)\n");
                break;

            case SIGBUS:
                printf("Bus error (SIGBUS)\n");
                break;

            case SIGILL:
                printf("Illegal instruction (SIGILL)\n");
                break;

            default:
                printf("Terminated by signal %d\n", sig);
        }
    }

    printf("--------------------------------\n");
}