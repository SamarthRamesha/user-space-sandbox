#include <stdio.h>
#include <sys/resource.h>
#include "resource_manager.h"

void apply_cpu_limit(int seconds)
{
    struct rlimit limit;

    limit.rlim_cur = seconds;
    limit.rlim_max = seconds;

    if(setrlimit(RLIMIT_CPU, &limit) < 0)
    {
        perror("CPU limit failed");
    }
}

void apply_memory_limit(int memory_mb)
{
    struct rlimit limit;

    limit.rlim_cur = memory_mb * 1024 * 1024;
    limit.rlim_max = memory_mb * 1024 * 1024;

    if(setrlimit(RLIMIT_AS, &limit) < 0)
    {
        perror("Memory limit failed");
    }
}
