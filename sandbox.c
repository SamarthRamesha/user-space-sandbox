#include <stdio.h>
#include "process_manager.h"
#include "monitor.h"

int main(int argc, char *argv[])
{
    if(argc < 2)
    {
        printf("Usage: ./sandbox <program>\n");
        return 1;
    }

    char *program = argv[1];
    char *args[] = {program, NULL};

    printf("Starting sandbox execution...\n");

    pid_t pid = launch_process(program, args);

    if(pid < 0)
    {
        printf("Sandbox failed to start program\n");
        return 1;
    }

    monitor_process(pid, program);

    return 0;
}