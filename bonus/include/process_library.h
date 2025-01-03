/*
** EPITECH PROJECT, 2024
** ftrace
** File description:
** process_library
*/

#ifndef PROCESSED_LIBRARY_H_
    #define PROCESSED_LIBRARY_H_

typedef struct {
    unsigned long start_addr;
    unsigned long end_addr;
    char *name;
} process_library_t;

process_library_t **parse_maps(int pid);
void free_maps(process_library_t **array);


#endif /* !PROCESSED_LIBRARY_H_ */
