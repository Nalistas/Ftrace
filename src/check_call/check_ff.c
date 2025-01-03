/*
** PERSONNAL PROJECT 2024
** ftrace
** File description:
** check_ff
*/

#include "myelf.h"
#include "ftrace.h"
#include "call_stack.h"

#include <stdio.h>
#include <sys/ptrace.h>
#include <stdlib.h>

static int temp_call(char *name, long value)
{
    call_stack_add(name, value);
    return CALL_HAPPENED;
}

static void set_regs_array(process_info_t *proc, long *regs)
{
    regs[0] = proc->regs.rax;
    regs[1] = proc->regs.rcx;
    regs[2] = proc->regs.rdx;
    regs[3] = proc->regs.rbx;
    regs[4] = proc->regs.rsp;
    regs[5] = proc->regs.rbp;
    regs[6] = proc->regs.rsi;
    regs[7] = proc->regs.rdi;
}

static int read_disp(process_info_t *ftrace, long addr)
{
    long text = ptrace(PTRACE_PEEKTEXT, ftrace->child_pid, addr);
    int disp = 0;

    if (text == -1)
        return -1;
    disp = text;
    return disp;
}

static int get_disp(process_info_t *ftrace, long rip, char modrm)
{
    int offset = (modrm % 8 == 4) ? 3 : 2;
    int disp = 0;

    if (modrm == 15 || modrm / 10 == 5 || modrm / 10 == 9) {
        disp = read_disp(ftrace, rip + offset);
        if (disp == -1)
            return -1;
        if (modrm / 10 == 5)
            disp &= 0xFF;
    }
    return disp;
}

static int check_ff2_call(process_info_t *proc, unsigned char modrm)
{
    long regs[8];
    int value = get_disp(proc, proc->regs.rip, modrm);
    char *name;

    if (value == -1)
        return CALL_HAPPENED;
    if (modrm % 8 == 4 && modrm != 0xD4) {
        name = create_function_name(proc->regs.rip, proc->exec_name);
        return temp_call(name, value);
    }
    set_regs_array(proc, regs);
    if (modrm != 0x15)
        value += regs[modrm % 8];
    name = get_function_name(proc, value);
    if (name != NULL) {
        return temp_call(name, value);
    }
    name = create_function_name(proc->regs.rip, proc->exec_name);
    return temp_call(name, value);
}

int check_ff_call(long peek1, process_info_t *proc)
{
    union {
        long nb;
        unsigned char instr[8];
    } data = {peek1};
    char modrm = data.instr[1];

    if (((modrm >> 3) & 0b111) == 2) {
        return check_ff2_call(proc, modrm);
    }
    dprintf(2, "unknown call 0x%lx\n", peek1);
    return CALL_HAPPENED;
}
