/*
** EPITECH PROJECT, 2024
** my_libelf2
** File description:
** myelf_iterator_manager
*/

#include "interface/myelf_manager.h"
#include "myelf.h"
#include "elffile/elffile.h"

static long myelf_get_value_info(elffile_t *elf, elf_iterrator_t *it,
    int id_info)
{
    if (it->type == MEFL_SYMBOL) {
        return ELFFILE_GET_SYM_DATA(elf, ELFFILE_ITER_GET(it->it), id_info);
    }
    if (it->type == MEFL_SECTION) {
        return ELFFILE_GET_SHDR_DATA(elf, ELFFILE_ITER_GET(it->it), id_info);
    }
    if (it->type == MELF_SEGMENT) {
        return ELFFILE_GET_PHDR_DATA(elf, ELFFILE_ITER_GET(it->it), id_info);
    }
    return 0;
}

long myelf_get_iterator_info(int id, int id_info)
{
    elffile_t *elffile = NULL;
    elf_iterrator_t *it = NULL;
    elf_manager_t *manager = myelf_manager();

    if (id < 0 || id >= manager->nb_it_max
        || manager->it_tab[id] == NULL)
        return 0;
    it = manager->it_tab[id];
    if (it->is_good == 0)
        return 0;
    if (it->elf_id < 0 || it->elf_id >= manager->nb_file_max
        || manager->file_tab[it->elf_id] == NULL) {
        it->is_good = 0;
        return 0;
    }
    elffile = manager->file_tab[it->elf_id];
    if (elffile == 0)
        return 0;
    return myelf_get_value_info(elffile, it, id_info);
}

void myelf_iterator_next(int id)
{
    if (id < 0 || id >= myelf_manager()->nb_it_max
        || myelf_manager()->it_tab[id] == NULL
        || myelf_manager()->it_tab[id]->is_good == 0)
        return;
    ELFFILE_ITER_INC(myelf_manager()->it_tab[id]->it);
}

int myelf_iterator_end(int id)
{
    if (id < 0 || id >= myelf_manager()->nb_it_max
        || myelf_manager()->it_tab[id] == NULL
        || myelf_manager()->it_tab[id]->is_good == 0) {
            return 1;
        }
    if (ELFFILE_ITER_END(myelf_manager()->it_tab[id]->it)) {
        myelf_manager()->it_tab[id]->is_good = 0;
        return 1;
    }
    return 0;
}
