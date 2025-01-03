/*
** PERSONNAL PROJECT 2024
** ftrace
** File description:
** get_sym_data32
*/


#include "elffile/elffile.h"
#include "elffile/b32/elf32.h"
#include <elf.h>

long get_sym_data32(void *ptr, size_t data)
{
    Elf32_Sym *sym = ptr;

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
