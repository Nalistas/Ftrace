/*
** PERSONNAL PROJECT 2024
** ftrace
** File description:
** ftrace_call_stack
*/

#include "ftrace.h"
#include "call_stack.h"

#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

static ftrace_call_stack_t *ftrace_call_stack(void)
{
    static ftrace_call_stack_t ftrace_call_stack;

    return &ftrace_call_stack;
}

void ftrace_call_stack_init(void)
{
    ftrace_call_stack()->call_stack = NULL;
}

void ftrace_call_stack_quit(void)
{
    call_stack_t *tmp = ftrace_call_stack()->call_stack;
    call_stack_t *next;

    while (tmp != NULL) {
        next = tmp->next;
        free(tmp->name);
        free(tmp);
        tmp = next;
    }
    ftrace_call_stack()->call_stack = NULL;
}

int call_stack_add(char *name, long value)
{
    call_stack_t *tmp = ftrace_call_stack()->call_stack;
    call_stack_t *new = malloc(sizeof(call_stack_t));

    if (new == NULL) {
        return 84;
    }
    new->name = name;
    new->next = tmp;
    dprintf(2, "Entering function %s at %#lx\n", name, (long)value);
    ftrace_call_stack()->call_stack = new;
    return 0;
}

int call_stack_pop(void)
{
    call_stack_t *tmp = ftrace_call_stack()->call_stack;

    if (tmp == NULL) {
        return 84;
    }
    ftrace_call_stack()->call_stack = tmp->next;
    dprintf(2, "Leaving function %s\n", tmp->name);
    free(tmp->name);
    free(tmp);
    return 0;
}
