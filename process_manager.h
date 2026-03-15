#ifndef PROCESS_MANAGER_H
#define PROCESS_MANAGER_H

#include <sys/types.h>

pid_t launch_process(char *program, char **args);

#endif