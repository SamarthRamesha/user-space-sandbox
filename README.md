# User-Space Sandbox

A lightweight user-space sandbox implemented in C that allows controlled execution of programs with CPU and memory limits. The project demonstrates core Operating System concepts like process creation, execution, monitoring, and resource management.

## Features

Interactive shell interface
Execute programs with CPU and memory limits
Process creation using `fork()`
Program execution using `execvp()`
Process monitoring using `waitpid()`
Signal handling (SIGSEGV, SIGXCPU, etc.)
Execution time tracking
Logging of execution results

## Concepts Used

Process Management
System Calls (POSIX)
Signals & Interrupts
Resource Limiting (`setrlimit`)
Parent-Child Process Model

## Supported Systems

This project uses POSIX system calls, so it works on:

### Supported:

Linux (Ubuntu, Arch, etc.)
macOS (Tested on MacBook with M-series chip)

### Not Supported (directly):
	Windows CMD / PowerShell

###️ Windows Users:
Use **WSL (Windows Subsystem for Linux)** to run this project.

## Execution

###Download the repository and navigate to this folder.
###Execute these commands:
	gcc sandbox.c process_manager.c monitor.c resource_manager.c -o sandbox
	./sandbox

###Inside the sandbox:
	to run programs: run --cpu <time limit in seconds> --mem <memory limit in MB> <./program_name>
	to exit the sandbox: exit

###programs to test have also been provided: 
	success_test_program.c
	crash_test_program.c
	loop_test_program.c
