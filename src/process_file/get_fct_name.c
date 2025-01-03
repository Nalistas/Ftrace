/*
** EPITECH PROJECT, 2024
** ftrace
** File description:
** get_fct_name
*/

#include "ftrace.h"
#include "myelf.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

char *create_function_name(long addr, char const *lib_name)
{
    char fct_name[1024] = {'\0'};

    sprintf(fct_name, "func_%#lx@%s", addr, lib_name);
    return strdup(fct_name);
}

char *get_function_name(process_info_t *ftrace, long addr)
{
    process_library_t *lib = get_lib(ftrace, addr);
    char *name = NULL;
    int elf_fd;

    if (lib == NULL) {
        return create_function_name(addr, ftrace->exec_name);
    }
    elf_fd = myelf_load(lib->name);
    if (elf_fd == -1) {
        return create_function_name(addr, lib->name);
    }
    name = find_symbol(ftrace, addr, elf_fd);
    if (name == NULL) {
        return create_function_name(addr, lib->name);
    }
    return name;
}
