/*
** PERSONNAL PROJECT 2024
** ftrace
** File description:
** get_process_lib
*/

#include "process_library.h"
#include "ftrace.h"
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

void free_maps(process_library_t **array)
{
    for (size_t i = 0; array[i] != NULL; i++) {
        free(array[i]->name);
        free(array[i]);
    }
    free(array);
}

void set_list_library(process_info_t *ftrace)
{
    process_library_t **array = NULL;

    array = parse_maps(ftrace->child_pid);
    if (array != NULL) {
        free_maps(ftrace->libs);
        ftrace->libs = array;
    }
}

process_library_t *find_library_by_address(process_info_t *ftrace,
    unsigned long addr)
{
    if (ftrace->libs == NULL)
        return NULL;
    for (size_t i = 0; ftrace->libs[i] != NULL; i++) {
        if (addr >= ftrace->libs[i]->start_addr &&
        addr <= ftrace->libs[i]->end_addr) {
            return ftrace->libs[i];
        }
    }
    return NULL;
}

process_library_t *find_library_by_name(process_info_t *ftrace,
    char const *name)
{
    if (ftrace->libs == NULL)
        return NULL;
    for (size_t i = 0; ftrace->libs[i] != NULL; i++) {
        if (strcmp(ftrace->libs[i]->name, name) == 0) {
            return ftrace->libs[i];
        }
    }
    return NULL;
}

process_library_t *get_lib(process_info_t *ftrace,
    unsigned long symbol_address)
{
    process_library_t *lib = NULL;

    lib = find_library_by_address(ftrace, symbol_address);
    if (!lib) {
        set_list_library(ftrace);
        return find_library_by_address(ftrace, symbol_address);
    }
    lib = find_library_by_address(ftrace, symbol_address);
    return lib;
}
