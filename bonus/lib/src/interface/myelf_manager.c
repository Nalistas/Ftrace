/*
** PERSONNAL PROJECT 2024
** ftrace
** File description:
** myelf_manager
*/

#include "interface/myelf_manager.h"
#include "elffile/elffile.h"
#include "myelf.h"

#include <stddef.h>
#include <string.h>

elf_manager_t *myelf_manager(void)
{
    static elf_manager_t manager = {
        .file_tab = NULL,
        .nb_file_max = 0,
        .it_tab = NULL,
        .nb_it_max = 0
    };

    return &manager;
}

int myelf_init(void)
{
    elf_manager_t *manager = myelf_manager();

    myelf_quit();
    manager->file_tab = malloc(sizeof(void *));
    if (manager->file_tab == NULL) {
        return -1;
    }
    manager->nb_file_max = 1;
    manager->file_tab[0] = NULL;
    manager->it_tab = malloc(sizeof(void *));
    if (manager->it_tab == NULL) {
        return -1;
    }
    manager->it_tab[0] = NULL;
    manager->nb_it_max = 1;
    return 0;
}

int myelf_quit(void)
{
    elf_manager_t *manager = myelf_manager();

    if (manager->file_tab != NULL) {
        for (int i = 0; i < manager->nb_file_max; i++) {
            myelf_unload(i);
        }
        free(manager->file_tab);
    }
    if (manager->it_tab != NULL) {
        for (int i = 0; i < manager->nb_it_max; i++) {
            free(manager->it_tab[i]);
        }
        free(manager->it_tab);
    }
    manager->file_tab = NULL;
    manager->nb_file_max = 0;
    manager->it_tab = NULL;
    manager->nb_it_max = 0;
    return 0;
}

int myelf_load(const char *f)
{
    elf_manager_t *m = myelf_manager();
    int i = myelf_get_existant_elf(f);

    if (i != -1)
        return i;
    for (i = 0; i < m->nb_file_max && m->file_tab[i]; i++);
    if (i == m->nb_file_max) {
        m->nb_file_max *= 2;
        m->file_tab = realloc(m->file_tab, sizeof(void *) * (m->nb_file_max));
        memset(m->file_tab + i, 0, sizeof(void *) * (m->nb_file_max - i));
    }
    m->file_tab[i] = malloc(sizeof(elffile_t));
    if (m->file_tab[i] != NULL && elffile_init(m->file_tab[i], f) == KO) {
        elffile_delete(m->file_tab[i]);
        free(m->file_tab[i]);
        m->file_tab[i] = NULL;
    }
    return (m->file_tab[i] == NULL) ? -1 : i;
}

int myelf_unload(int id)
{
    if (id < 0 || id >= myelf_manager()->nb_file_max
        || myelf_manager()->file_tab[id] == NULL)
        return -1;
    elffile_delete(myelf_manager()->file_tab[id]);
    free(myelf_manager()->file_tab[id]);
    myelf_manager()->file_tab[id] = NULL;
    return 0;
}
