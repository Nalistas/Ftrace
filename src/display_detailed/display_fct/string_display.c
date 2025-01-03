/*
** EPITECH PROJECT, 2024
** strace
** File description:
** string_display
*/

#include "gnu_source.h"
#include <string.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ptrace.h>
#include <sys/types.h>

static char is_the_end(long data)
{
    char *ptr = (char *)&data;

    for (size_t i = 0; i < sizeof(long); ++i) {
        if (ptr[i] == 0) {
            return 1;
        }
    }
    return 0;
}

static void *get_str(long addr, pid_t childpid)
{
    size_t bytes_read = 0;
    size_t size = sizeof(long);
    char *buffer = malloc(size + 1);
    long data;

    do {
        data = ptrace(PTRACE_PEEKDATA, childpid, addr + bytes_read, NULL);
        if (errno != 0) {
            free(buffer);
            return NULL;
        }
        *((long *)((char *)buffer + bytes_read)) = data;
        bytes_read += sizeof(long);
        if (bytes_read + 1 >= size) {
            size *= 2;
            buffer = realloc(buffer, size + 1);
        }
    } while (!is_the_end(data));
    buffer[size] = 0;
    return buffer;
}

void string_display(int current_param,
    long long int const args[7], pid_t childpid)
{
    char *str = get_str(args[current_param], childpid);

    if (str != NULL) {
        dprintf(STDERR_FILENO, "\"%s\"", str);
        free(str);
    } else {
        dprintf(STDERR_FILENO, "NULL");
    }
}
