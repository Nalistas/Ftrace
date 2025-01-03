/*
** EPITECH PROJECT, 2024
** my_libelf2
** File description:
** get_sym_data64
*/


#include "elffile/elffile.h"
#include "elffile/b64/elf64.h"
#include <elf.h>

long get_sym_data64(void *ptr, size_t data)
{
    Elf64_Sym *sym = ptr;

    switch (data) {
    case SYM_NAME:
        return sym->st_name;
    case SYM_INFO:
        return sym->st_info;
    case SYM_SHNDX:
        return sym->st_shndx;
    case SYM_VALUE:
        return sym->st_value;
    case SYM_SIZE:
        return sym->st_size;
    }
    return 0;
}
