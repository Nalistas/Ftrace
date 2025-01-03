/*
** PERSONNAL PROJECT 2024
** ftrace
** File description:
** myelf_get_tab
*/

#include "interface/myelf_manager.h"
#include "myelf.h"
#include "elffile/elffile.h"

void *myelf_get_symtab_ptr(int id)
{
    elffile_t *elffile;

    if (id < 0 || id >= myelf_manager()->nb_file_max
        || myelf_manager()->file_tab[id] == NULL)
        return NULL;
    elffile = myelf_manager()->file_tab[id];
    return elffile->symbol_table;
}

void *myelf_get_strtab_ptr(int id)
{
    elffile_t *elffile;

    if (id < 0 || id >= myelf_manager()->nb_file_max
        || myelf_manager()->file_tab[id] == NULL)
        return NULL;
    elffile = myelf_manager()->file_tab[id];
    return ELFFILE_GET_SECTION_BY_NAME(elffile, ".strtab");
}

void *myelf_get_phdrtab_ptr(int id)
{
    int info;
    elffile_t *elffile;

    if (id < 0 || id >= myelf_manager()->nb_file_max
        || myelf_manager()->file_tab[id] == NULL)
        return NULL;
    elffile = myelf_manager()->file_tab[id];
    info = ELFFILE_GET_EHDR_DATA(elffile, E_PHOFF);
    if (info == 0)
        return NULL;
    return elffile->file + (intptr_t)info;
}

void *myelf_get_shdrtab_ptr(int id)
{
    elffile_t *elffile;

    if (id < 0 || id >= myelf_manager()->nb_file_max
        || myelf_manager()->file_tab[id] == NULL)
        return NULL;
    elffile = myelf_manager()->file_tab[id];
    return elffile->section_header;
}
