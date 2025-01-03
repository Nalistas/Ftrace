/*
** EPITECH PROJECT, 2024
** strace
** File description:
** detailing_fct
*/

#include "my_syscall.h"
#include <sys/types.h>
#include <stdbool.h>

#ifndef DETAILING_FCT_H_
    #define DETAILING_FCT_H_


typedef void (*detailing_fct_t)(int current_param,
    long long int const args[6], pid_t childpid);

void string_display(int current_param,
    long long int const args[6], pid_t childpid);

void display_sized_ptr(int current_param,
    long long int const args[6], pid_t childpid);

void default_display(int current_param,
    long long int const args[6], pid_t childpid);

void num_display(int current_param,
    long long int const args[6], pid_t childpid);

void unsigned_display(int current_param,
    long long int const args[6], pid_t childpid);

struct dict_fct {
    int id;
    detailing_fct_t fct;
};

static const struct dict_fct fct_tab[] = {
    {STRING, string_display}, // Utilisation de la fonction string_display
    {SIZED_PTR, display_sized_ptr},
    {CONST_SIZED_PTR, display_sized_ptr},
    {VOID_P, default_display},
    {NUM, num_display},
    {UNSIGNED, unsigned_display},
};

static const struct dict_fct fct_tab_in_case_of_fail[] = {
    {STRING, string_display}, // Utilisation de la fonction string_display
    {SIZED_PTR, default_display},
    {CONST_SIZED_PTR, default_display},
    {VOID_P, default_display},
    {NUM, num_display},
    {UNSIGNED, unsigned_display},
};

    #define SIZE_FCT_TAB    sizeof(fct_tab) / sizeof(struct dict_fct)

#endif /* !DETAILING_FCT_H_ */
