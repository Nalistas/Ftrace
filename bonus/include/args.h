/*
** EPITECH PROJECT, 2024
** strace
** File description:
** args
*/

#include "my_syscall.h"

#ifndef ARGS_H_
    #define ARGS_H_

static const char *args_messages[] = {
    "() ",
    "(0x%llx) ",
    "(0x%llx, 0x%llx) ",
    "(0x%llx, 0x%llx, 0x%llx) ",
    "(0x%llx, 0x%llx, 0x%llx, 0x%llx) ",
    "(0x%llx, 0x%llx, 0x%llx, 0x%llx, 0x%llx) ",
    "(0x%llx, 0x%llx, 0x%llx, 0x%llx, 0x%llx, 0x%llx) ",
};



#endif /* !ARGS_H_ */
