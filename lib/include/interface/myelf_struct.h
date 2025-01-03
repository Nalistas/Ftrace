/*
** PERSONNAL PROJECT 2024
** ftrace
** File description:
** myelf_struct
*/

#include "elffile/elffile.h"

#ifndef MYELF_STRUCT_H_
    #define MYELF_STRUCT_H_

enum MELF_ITER_TYPE {
    MEFL_SYMBOL,
    MEFL_SECTION,
    MELF_SEGMENT
};

typedef struct elf_iterrator {
    elf_tab_it_t it;
    enum MELF_ITER_TYPE type;
    int elf_id;
    int is_good;
} elf_iterrator_t;


typedef struct elf_manager {
    elffile_t **file_tab;
    int nb_file_max;
    elf_iterrator_t **it_tab;
    int nb_it_max;
} elf_manager_t;

#endif /* !MYELF_STRUCT_H_ */
