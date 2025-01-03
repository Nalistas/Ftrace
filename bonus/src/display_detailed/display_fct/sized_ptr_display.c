/*
** PERSONNAL PROJECT 2024
** ftrace
** File description:
** sized_ptr_display
*/

#include "ftrace.h"
#include <sys/types.h>
#include <stddef.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <ctype.h>

void display_sized_ptr(int current_param,
    long long int const args[7], pid_t childpid)
{
    char str[129];
    char *tmp = str;
    size_t size = args[current_param + 1];
    unsigned char *data;

    if (args[current_param] == 0) {
        dprintf(STDERR_FILENO, "NULL");
        return;
    }
    data = get_sized_param(size, args[current_param], childpid);
    if (data == NULL)
        return;
    memset(str, 0, sizeof(str));
    for (size_t i = 0; i < 32 && i < size; ++i)
        tmp += sprintf(tmp, (isprint(data[i])) ? "%c" : "\\%hho", data[i]);
    str[128] = 0;
    dprintf(STDERR_FILENO, "\"%s\"", str);
    if (size > 32) {
        dprintf(STDERR_FILENO, "...");
    }
}
