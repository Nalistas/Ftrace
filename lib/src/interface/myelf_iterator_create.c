/*
** PERSONNAL PROJECT 2024
** ftrace
** File description:
** myelf_iterator_create
*/

#include "interface/myelf_manager.h"
#include "myelf.h"
#include "elffile/elffile.h"

#include <string.h>

static int create_new_iterator(elf_manager_t *manager, int id)
{
    int i = 0;

    if (manager->it_tab == NULL)
        return -1;
    while (i < manager->nb_it_max && manager->it_tab[i]
        && manager->it_tab[i]->is_good == 1)
        i++;
    if (i == manager->nb_it_max) {
        manager->nb_it_max *= 2;
        manager->it_tab = realloc(manager->it_tab,
            sizeof(void *) * (manager->nb_it_max));
        memset(manager->it_tab + i, 0,
            sizeof(void *) * (manager->nb_it_max - i));
    }
    manager->it_tab[i] = realloc(manager->it_tab[i], sizeof(elf_iterrator_t));
    if (manager->it_tab[i] == NULL)
        return -1;
    memset(manager->it_tab[i], 0, sizeof(elf_iterrator_t));
    manager->it_tab[i]->elf_id = id;
    return i;
}

int myelf_create_phdr_iterator(int id)
{
    int id_it;
    elf_manager_t *manager = myelf_manager();

    if (id < 0 || id >= manager->nb_file_max
        || manager->file_tab[id] == NULL)
        return -1;
    id_it = create_new_iterator(manager, id);
    if (id_it == -1)
        return -1;
    manager->it_tab[id_it]->type = MELF_SEGMENT;
    manager->it_tab[id_it]->is_good = 1;
    manager->it_tab[id_it]->it = ELFFILE_PHDR_ITER(manager->file_tab[id]);
    return id_it;
}

int myelf_create_shdr_iterator(int id)
{
    int id_it;
    elf_manager_t *manager = myelf_manager();

    if (id < 0 || id >= manager->nb_file_max
        || manager->file_tab[id] == NULL)
        return -1;
    id_it = create_new_iterator(manager, id);
    if (id_it == -1)
        return -1;
    manager->it_tab[id_it]->type = MEFL_SECTION;
    manager->it_tab[id_it]->is_good = 1;
    manager->it_tab[id_it]->it = ELFFILE_SHDR_ITER(manager->file_tab[id]);
    return id_it;
}

int myelf_create_sym_iterator(int id)
{
    int id_it;
    elf_manager_t *manager = myelf_manager();

    if (id < 0 || id >= manager->nb_file_max
        || manager->file_tab[id] == NULL)
        return -1;
    id_it = create_new_iterator(manager, id);
    if (id_it == -1)
        return -1;
    manager->it_tab[id_it]->type = MEFL_SYMBOL;
    manager->it_tab[id_it]->is_good = 1;
    manager->it_tab[id_it]->it = ELFFILE_SYM_ITER(manager->file_tab[id]);
    return id_it;
}
