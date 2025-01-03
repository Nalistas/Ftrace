/*
** EPITECH PROJECT, 2024
** strace
** File description:
** default_display
*/

#include "gnu_source.h"

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <errno.h>
#include <string.h>
#include <strings.h>

void num_display(int current_param,
    long long int const args[7], __attribute__((unused)) pid_t childpid)
{
    if (current_param == 6 && args[current_param] < 0) {
        dprintf(STDERR_FILENO, "-1 %s (%s)", strerrorname_np(args[6] * -1),
        strerror(args[6] * -1));
    } else {
        dprintf(STDERR_FILENO, "%lld", args[current_param]);
    }
}

void unsigned_display(int current_param,
    long long int const args[7], __attribute__((unused)) pid_t childpid)
{
    dprintf(STDERR_FILENO, "%llu", args[current_param]);
}

void default_display(int current_param,
    long long int const args[7], __attribute__((unused)) pid_t childpid)
{
    if (args[current_param] == 0) {
        dprintf(STDERR_FILENO, "NULL");
    } else {
        dprintf(STDERR_FILENO, "0x%llx", args[current_param]);
    }
}
