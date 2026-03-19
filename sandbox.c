#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "process_manager.h"
#include "monitor.h"

#define MAX_INPUT 256

int main()
{
    char input[MAX_INPUT];

    // Header
    printf("\n----------------------------------\n");
    printf("   User-Space Sandbox (v1.0)\n");
    printf("----------------------------------\n");
    printf("Commands:\n");
    printf("  run --cpu <sec> --mem <MB> <program>\n");
    printf("  exit\n\n");

    while(1)
    {
        printf("sandbox> ");

        // Take input
        if(fgets(input, MAX_INPUT, stdin) == NULL)
            continue;

        // Remove newline
        input[strcspn(input, "\n")] = 0;

        // Exit command
        if(strcmp(input, "exit") == 0)
        {
            printf("\nExiting sandbox...\n");
            break;
        }

        // Validate command
        if(strncmp(input, "run", 3) != 0)
        {
            printf("Invalid command. Use 'run' or 'exit'\n");
            continue;
        }

        int cpu_limit = 2;
        int mem_limit = 64;
        char program[100];

        // Parse input
        int parsed = sscanf(input,
                            "run --cpu %d --mem %d %s",
                            &cpu_limit, &mem_limit, program);

        if(parsed < 3)
        {
            printf("Invalid format!\n");
            printf("Usage: run --cpu <sec> --mem <MB> <program>\n");
            continue;
        }

        char *args[] = {program, NULL};

        // Info print
        printf("\n[INFO] Starting execution...\n");
        printf("       CPU Limit   : %d sec\n", cpu_limit);
        printf("       Memory Limit: %d MB\n\n", mem_limit);

        // Launch process
        pid_t pid = launch_process(program, args, cpu_limit, mem_limit);

        if(pid < 0)
        {
            printf("[ERROR] Failed to start program\n");
            continue;
        }

        // Monitor process
        monitor_process(pid, program);
    }

    return 0;
}