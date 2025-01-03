/*
** PERSONNAL PROJECT 2024
** ftrace
** File description:
** myelf_get_existant_elf
*/

#include "interface/myelf_manager.h"

#include <string.h>

int myelf_get_existant_elf(char const *filename)
{
    elf_manager_t *manager = myelf_manager();
    int i = 0;

    for (i = 0; i < manager->nb_file_max
        && manager->file_tab[i] != NULL; i++) {
        if (strcmp(manager->file_tab[i]->namefile, filename) == 0)
            return i;
    }
    return -1;
}
