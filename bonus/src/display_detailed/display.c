/*
** EPITECH PROJECT, 2024
** strace
** File description:
** display
*/

#include <sys/user.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/ptrace.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>

#include "detailing_fct.h"

void *get_sized_param(size_t size, long addr, pid_t childpid)
{
    static void *buffer = NULL;
    long data;
    size_t bytes_read = 0;

    if (buffer != NULL) {
        free(buffer);
        buffer = NULL;
    }
    if (size == 0)
        return buffer;
    buffer = malloc(size + (sizeof(long) - (size % sizeof(long))));
    errno = 0;
    while (bytes_read < size) {
        data = ptrace(PTRACE_PEEKDATA, childpid, addr + bytes_read, NULL);
        if (errno != 0)
            return NULL;
        *((long *)((char *)buffer + bytes_read)) = data;
        bytes_read += sizeof(long);
    }
    return buffer;
}

static detailing_fct_t get_fct(int type, const struct dict_fct *tab,
    size_t size)
{
    for (size_t i = 0; i < size; ++i) {
        if (tab[i].id == type) {
            return tab[i].fct;
        }
    }
    return NULL;
}

static char is_in_the_list(int check, int const tab[], size_t size_of_tab)
{
    for (size_t i = 0; i < size_of_tab; ++i) {
        if (tab[i] == check) {
            return 1;
        }
    }
    return 0;
}

void display_param(int current_param,
    int const args_type[7],
    long long int const args[7], pid_t childpid)
{
    detailing_fct_t fct;
    int tab_num[] = {NUM, CLOCK_T, TIME_T, KEY_SERIAL_T};
    size_t sz_tab_neg = sizeof(tab_num) / sizeof(int);
    int tab_ptr[] = {VOID_P};
    size_t sz_tab0 = sizeof(tab_ptr) / sizeof(int);

    if ((args[6] < 0 && is_in_the_list(args_type[6], tab_num, sz_tab_neg)) ||
        (args[6] == 0 && is_in_the_list(args_type[6], tab_ptr, sz_tab0))) {
        fct = get_fct(args_type[current_param], fct_tab_in_case_of_fail,
            SIZE_FCT_TAB);
    } else {
        fct = get_fct(args_type[current_param], fct_tab, SIZE_FCT_TAB);
    }
    if (fct == NULL)
        default_display(current_param, args, childpid);
    else {
        fct(current_param, args, childpid);
    }
    (void)table;
}

void display_args_detailed(struct user_regs_struct *regs, syscall_t *sym,
    pid_t childpid)
{
    int args_type[7] = {sym->arg1t, sym->arg2t, sym->arg3t,
        sym->arg4t, sym->arg5t, sym->arg6t, sym->retval};
    long long int args[7] = {regs->rdi, regs->rsi, regs->rdx,
        regs->rcx, regs->r8, regs->r9, regs->rax};

    if (sym->nb_args > 6)
        return;
    write(STDERR_FILENO, "(", 1);
    for (int i = 0; i < sym->nb_args && args_type[i] != 0; ++i) {
        display_param(i, args_type, args, childpid);
        if (i < sym->nb_args - 1)
            write(STDERR_FILENO, ", ", 2);
    }
    if (sym->retval == VOID)
        dprintf(STDERR_FILENO, ") = ?\n");
    else {
        dprintf(STDERR_FILENO, ") = ");
        display_param(6, args_type, args, childpid);
        write(STDERR_FILENO, "\n", 1);
    }
}
