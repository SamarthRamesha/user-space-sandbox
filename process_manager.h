#ifndef PROCESS_MANAGER_H
#define PROCESS_MANAGER_H

#include <sys/types.h>

pid_t launch_process(char *program, char **args,
                     int cpu_limit, int mem_limit);

#endif
