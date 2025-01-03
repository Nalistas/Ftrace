/*
** EPITECH PROJECT, 2024
** ftrace
** File description:
** check_call
*/

#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/ptrace.h>

#include "ftrace.h"
#include "myelf.h"
#include "call_stack.h"

static int manage_call(long peek1, process_info_t *proc)
{
    if (((unsigned char *)&peek1)[0] == 0xe8) {
        check_e8_call(peek1, proc);
    }
    if (((unsigned char *)&peek1)[0] == 0xff) {
        check_ff_call(peek1, proc);
    }
    return CALL_HAPPENED;
}

int manage_call_ret(long peek1, process_info_t *proc)
{
    int retval = manage_call(peek1, proc)
        != NOTHING_HAPPENED;

    if ((peek1 & 0xFF) == 0xc3
        || (peek1 & 0xFF) == 0xcb
        || (peek1 & 0xFF) == 0xc2
        || (peek1 & 0xFF) == 0xca) {
            call_stack_pop();
    }
    return retval;
}
