/*
** EPITECH PROJECT, 2024
** my_libelf2
** File description:
** get_phdr_data32
*/

#include <elf.h>
#include <stddef.h>
#include "elffile/elffile.h"

long get_phdr_data32(void *ptr, size_t data)
{
    switch (data) {
    case PH_TYPE:
        return ((Elf32_Phdr *)ptr)->p_type;
    case PH_OFFSET:
        return ((Elf32_Phdr *)ptr)->p_offset;
    case PH_VADDR:
        return ((Elf32_Phdr *)ptr)->p_vaddr;
    case PH_PADDR:
        return ((Elf32_Phdr *)ptr)->p_paddr;
    case PH_FILESZ:
        return ((Elf32_Phdr *)ptr)->p_filesz;
    case PH_MEMSZ:
        return ((Elf32_Phdr *)ptr)->p_memsz;
    case PH_FLAGS:
        return ((Elf32_Phdr *)ptr)->p_flags;
    case PH_ALIGN:
        return ((Elf32_Phdr *)ptr)->p_align;
    }
    return 0;
}
