/*
** PERSONNAL PROJECT 2024
** ftrace
** File description:
** execve_case
*/


#include <sys/ptrace.h>
#include <sys/wait.h>
#include <sys/reg.h>
#include <sys/types.h>
#include <sys/user.h>
#include <stdbool.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <bits/waitflags.h>

#include "ftrace.h"
#include "my_syscall.h"

static void display_return_value(struct user_regs_struct *regs, pid_t childpid,
    int args_type[7], long long int args[7])
{
    ptrace(PTRACE_GETREGS, childpid, NULL, regs);
    if (args_type[6] == VOID)
        dprintf(STDERR_FILENO, ") = ?\n");
    else {
        args[6] = regs->rax;
        dprintf(STDERR_FILENO, ") = ");
        display_param(6, args_type, args, childpid);
        write(STDERR_FILENO, "\n", 1);
    }
}

int manage_execve(struct user_regs_struct *regs, pid_t childpid)
{
    int status;
    syscall_t sym = table[regs->rax];
    int args_type[7] = {sym.arg1t, sym.arg2t, sym.arg3t,
        sym.arg4t, sym.arg5t, sym.arg6t, sym.retval};
    long long int args[7] = {regs->rdi, regs->rsi, regs->rdx,
        regs->rcx, regs->r8, regs->r9, regs->rax};

    if (sym.nb_args > 6)
        return 84;
    write(STDERR_FILENO, "(", 1);
    for (int i = 0; i < sym.nb_args && args_type[i] != 0; ++i) {
        display_param(i, args_type, args, childpid);
        if (i < sym.nb_args - 1)
            write(STDERR_FILENO, ", ", 2);
    }
    ptrace(PTRACE_SINGLESTEP, childpid, NULL, NULL);
    if (wait4(childpid, &status, WUNTRACED | WCONTINUED, NULL) < 0)
        return 84;
    display_return_value(regs, childpid, args_type, args);
    return 0;
}
