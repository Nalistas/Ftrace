/*
** EPITECH PROJECT, 2024
** my_libelf2
** File description:
** myelf_basic_data_getter
*/

#include "interface/myelf_manager.h"
#include "myelf.h"

int myelf_get_mod32x64(int id)
{
    int result = -1;

    if (id < 0 || id >= myelf_manager()->nb_file_max
        || myelf_manager()->file_tab[id] == NULL)
        return -1;
    result = ELFFILE_GET_MOD32X64(myelf_manager()->file_tab[id]);
    if (result == 1)
        return 32;
    if (result == 2)
        return 64;
    return -1;
}

int myelf_get_entry(int id)
{
    if (id < 0 || id >= myelf_manager()->nb_file_max
        || myelf_manager()->file_tab[id] == NULL)
        return -1;
    return ELFFILE_GET_EHDR_DATA(myelf_manager()->file_tab[id], E_ENTRY);
}

char const *myelf_get_raw_file(int id)
{
    if (id < 0 || id >= myelf_manager()->nb_file_max
        || myelf_manager()->file_tab[id] == NULL)
        return NULL;
    return myelf_manager()->file_tab[id]->file;
}

char const *myelf_get_file_name(int id)
{
    if (id < 0 || id >= myelf_manager()->nb_file_max
        || myelf_manager()->file_tab[id] == NULL)
        return NULL;
    return myelf_manager()->file_tab[id]->namefile;
}
