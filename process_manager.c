#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include "process_manager.h"
#include "resource_manager.h"

pid_t launch_process(char *program, char **args,
                     int cpu_limit, int mem_limit)
{
    pid_t pid = fork();

    if(pid < 0)
    {
        perror("Fork failed");
        return -1;
    }

    if(pid == 0)
    {
        // CHILD PROCESS

        apply_cpu_limit(cpu_limit);
        apply_memory_limit(mem_limit);

        execvp(program, args);

        perror("Execution failed");
        _exit(1);
    }

    return pid;
}
