/*
** EPITECH PROJECT, 2024
** strace
** File description:
** launch_ftrace
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
#include "args.h"
#include "process_library.h"

#include "myelf.h"

void display_args_hex(struct user_regs_struct *regs, syscall_t *sym,
    __attribute__((unused)) pid_t childpid)
{
    if (sym->nb_args > 6) {
        return;
    }
    dprintf(STDERR_FILENO, args_messages[sym->nb_args], regs->rdi, regs->rsi,
        regs->rdx, regs->rcx, regs->r8, regs->r9);
    if (table[sym->id].retval == VOID) {
        dprintf(STDERR_FILENO, " = ?\n");
    } else {
        dprintf(STDERR_FILENO, " = 0x%llx\n", regs->rax);
    }
}

static int manage_syscall(process_info_t *proc, int instr)
{
    static bool need_to_check_rax = false;
    static int last_syscall = 0;
    static struct user_regs_struct prv_rgs_state;
    display_fct_t fct = display_args_hex;

    if (need_to_check_rax) {
        need_to_check_rax = false;
        prv_rgs_state.rax = proc->regs.rax;
        fct(&prv_rgs_state, &table[last_syscall], proc->child_pid);
    }
    if ((IS_KERNELCALL(instr) || instr == 0) && proc->regs.rax < NB_SYSCALL) {
        dprintf(STDERR_FILENO, "Syscall %s", table[proc->regs.rax].name);
        memcpy(&prv_rgs_state, &(proc->regs), sizeof(struct user_regs_struct));
        last_syscall = proc->regs.rax;
        need_to_check_rax = true;
    }
    return 0;
}

static int iterate_proc(process_info_t *process)
{
    long instr;

    ptrace(PTRACE_GETREGS, process->child_pid, NULL, &(process->regs));
    instr = ptrace(PTRACE_PEEKDATA, process->child_pid,
        process->regs.rip, NULL);
    manage_call_ret(instr, process);
    if (manage_syscall(process, instr) != 0) {
        return 84;
    }
    ptrace(PTRACE_SINGLESTEP, process->child_pid, NULL, NULL);
    if (wait4(process->child_pid, &(process->status),
        WUNTRACED | WCONTINUED, NULL) < 0) {
        return 84;
    }
    return 0;
}

int launch_ftrace(pid_t child_pid, char const *exec_name)
{
    process_info_t process_info = {
        .child_pid = child_pid,
        .status = -1,
        .libs = parse_maps(child_pid),
        .regs = {0},
        .exec_name = exec_name
    };

    while (!WIFEXITED(process_info.status)) {
        if (iterate_proc(&process_info) != 0)
            return 84;
    }
    manage_syscall(&process_info, -1);
    dprintf(STDERR_FILENO, "+++ exited with %d +++\n",
        WEXITSTATUS(process_info.status));
    get_sized_param(0, 0, 0);
    free_maps(process_info.libs);
    return WEXITSTATUS(process_info.status);
}
