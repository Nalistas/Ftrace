/*
** EPITECH PROJECT, 2024
** my_libelf2
** File description:
** myelf_request
*/

#include "interface/myelf_manager.h"

char const *myelf_get_string_table(int id)
{
    elffile_t *elffile;

    if (id < 0 || id >= myelf_manager()->nb_file_max
        || myelf_manager()->file_tab[id] == NULL)
        return NULL;
    elffile = myelf_manager()->file_tab[id];
    return elffile->string_table;
}

char const *myelf_get_symstring_table(int id)
{
    elffile_t *elffile;
    char *ptr = NULL;

    if (id < 0 || id >= myelf_manager()->nb_file_max
        || myelf_manager()->file_tab[id] == NULL)
        return NULL;
    elffile = myelf_manager()->file_tab[id];
    ptr = ELFFILE_GET_SECTION_BY_NAME(elffile, ".strtab");
    if (ptr == NULL)
        return NULL;
    return elffile->file +
        (intptr_t)ELFFILE_GET_SHDR_DATA(elffile, ptr, SH_OFFSET);
}
