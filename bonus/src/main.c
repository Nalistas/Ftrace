/*
** PERSONNAL PROJECT 2024
** ftrace
** File description:
** main
*/

#include <sys/ptrace.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>
#include <stdio.h>

#include "ftrace.h"
#include "myelf.h"
#include "call_stack.h"

int trace_me(char **av, char **env)
{
    pid_t child_pid;
    int status;

    child_pid = fork();
    if (child_pid == -1) {
        return 84;
    }
    if (child_pid == 0) {
        ptrace(PTRACE_TRACEME, 0, NULL, NULL);
        execve(av[1], av + 1, env);
        return 0;
    }
    waitpid(child_pid, &status, 0);
    if (ptrace(PTRACE_SETOPTIONS, child_pid, 0, PTRACE_O_TRACEEXIT) == -1)
        return -1;
    if (ptrace(PTRACE_SINGLESTEP, child_pid, 0, 0) == -1)
        return -1;
    return launch_ftrace(child_pid, av[1]);
}

int main(int ac, char **av, char **env)
{
    int status = 0;
    int elffile;

    if (ac == 1)
        return 84;
    if (ac < 2)
        return 84;
    myelf_init();
    ftrace_call_stack_init();
    elffile = myelf_load(av[1]);
    if (elffile == -1) {
        return 84;
    }
    status = trace_me(av, env);
    myelf_quit();
    ftrace_call_stack_quit();
    return status;
}
