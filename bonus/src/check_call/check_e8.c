/*
** PERSONNAL PROJECT 2024
** ftrace
** File description:
** check_e8
*/

#include "myelf.h"
#include "ftrace.h"
#include "call_stack.h"
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int check_e8_call(long peek1, process_info_t *proc)
{
    union data {
        long nb;
        unsigned char instr[8];
    } offset = {peek1};
    int ptr = 0;
    long symbol_addr = 0;
    char *f_name = NULL;
    process_library_t *lib = NULL;

    memcpy(&ptr, (char *)&(offset.instr[1]), sizeof(int));
    symbol_addr = ((long)proc->regs.rip + 5 + (long)ptr);
    f_name = get_function_name(proc, symbol_addr);
    if (f_name != NULL) {
        lib = get_lib(proc, symbol_addr);
        call_stack_add(f_name,
            (lib != NULL) ? lib->name : proc->exec_name , symbol_addr);
    }
    return CALL_HAPPENED;
}
