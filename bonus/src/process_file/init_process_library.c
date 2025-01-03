/*
** EPITECH PROJECT, 2024
** ftrace
** File description:
** init_process_library
*/

#include "process_library.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

static process_library_t *create_data(char *name, char *start, char *end)
{
    process_library_t *new = malloc(sizeof(process_library_t));
    char *ptr_start = start;
    char *ptr_end = end;

    new->name = strdup(name);
    new->start_addr = strtol(start, &ptr_start, 16);
    new->end_addr = strtol(end, &ptr_end, 16);
    return new;
}

static process_library_t *get_data(char *line)
{
    char *name = NULL;
    char *start = NULL;
    char *end = NULL;

    start = strsep(&line, " -");
    end = strsep(&line, " -");
    if (strstr(line, "/") != NULL) {
        name = strstr(line, "/");
        return create_data(name, start, end);
    }
    return NULL;
}

static int fdgetline(int fd, char **line_ptr)
{
    char *line = *line_ptr;
    size_t space = 1;
    size_t i = 0;

    line = realloc(line, sizeof(char[space + 1]));
    if (line == NULL || fd < 0)
        return -1;
    memcpy(line, "\0\0", 2);
    for (; read(fd, line + i, 1) > 0 && line[i] != '\n'; ++i) {
        if (i == space) {
            space <<= 1;
            line = realloc(line, sizeof(char[space + 1]));
            line[space] = 0;
        }
    }
    *line_ptr = line;
    if (line[i] != '\n')
        return -1;
    line[i] = 0;
    return i;
}

process_library_t **parse_maps(int pid)
{
    int fd;
    char *line = NULL;
    char path[255] = {'\0'};
    size_t i = 0;
    process_library_t **array = malloc(sizeof(process_library_t *));
    process_library_t *new;

    sprintf(path, "/proc/%d/maps", pid);
    fd = open(path, O_RDONLY);
    while (fdgetline(fd, &line) != -1) {
        new = get_data(line);
        array = realloc(array, sizeof(process_library_t *) * (i + 2));
        array[i] = new;
        i += (new != NULL) ? 1 : 0;
    }
    array[i] = NULL;
    close(fd);
    free(line);
    return array;
}
