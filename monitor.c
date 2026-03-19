#include <stdio.h>
#include <sys/wait.h>
#include <signal.h>
#include <sys/time.h>
#include "monitor.h"

void monitor_process(pid_t pid, char *program)
{
    int status;

    struct timeval start, end;
    gettimeofday(&start, NULL);

    waitpid(pid, &status, 0);

    gettimeofday(&end, NULL);

    double exec_time =
        (end.tv_sec - start.tv_sec) +
        (end.tv_usec - start.tv_usec) / 1000000.0;

    FILE *log_file = fopen("sandbox_log.txt", "a");

    printf("\n--- Sandbox Execution Report ---\n");
    printf("Program : %s\n", program);
    printf("PID     : %d\n", pid);
    printf("Execution Time : %.3f sec\n", exec_time);

    fprintf(log_file, "\n--- Sandbox Execution Report ---\n");
    fprintf(log_file, "Program : %s\n", program);
    fprintf(log_file, "PID     : %d\n", pid);
    fprintf(log_file, "Execution Time : %.3f sec\n", exec_time);

    if(WIFEXITED(status))
    {
        printf("Result  : Program exited normally\n");
        printf("Exit Code : %d\n", WEXITSTATUS(status));

        fprintf(log_file, "Result  : Program exited normally\n");
        fprintf(log_file, "Exit Code : %d\n", WEXITSTATUS(status));
    }

    else if(WIFSIGNALED(status))
    {
        int sig = WTERMSIG(status);

        printf("Result  : ");
        fprintf(log_file, "Result  : ");

        switch(sig)
        {
            case SIGXCPU:
                printf("CPU time limit exceeded\n");
                fprintf(log_file, "CPU time limit exceeded\n");
                break;

            case SIGSEGV:
                printf("Segmentation Fault\n");
                fprintf(log_file, "Segmentation Fault\n");
                break;

            case SIGKILL:
                printf("Process killed\n");
                fprintf(log_file, "Process killed\n");
                break;

            default:
                printf("Terminated by signal %d\n", sig);
                fprintf(log_file, "Terminated by signal %d\n", sig);
        }
    }

    printf("--------------------------------\n");
    fprintf(log_file, "--------------------------------\n");

    fclose(log_file);
}
