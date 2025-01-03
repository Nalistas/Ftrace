/*
** PERSONNAL PROJECT 2024
** ftrace
** File description:
** get_phdr_data32
*/

#include "elffile/elffile.h"
#include <stdio.h>

long get_phdr_data64(void *ptr, size_t data)
{
    switch (data) {
    case PH_TYPE:
        return ((Elf64_Phdr *)ptr)->p_type;
    case PH_OFFSET:
        return ((Elf64_Phdr *)ptr)->p_offset;
    case PH_VADDR:
        return ((Elf64_Phdr *)ptr)->p_vaddr;
    case PH_PADDR:
        return ((Elf64_Phdr *)ptr)->p_paddr;
    case PH_FILESZ:
        return ((Elf64_Phdr *)ptr)->p_filesz;
    case PH_MEMSZ:
        return ((Elf64_Phdr *)ptr)->p_memsz;
    case PH_FLAGS:
        return ((Elf64_Phdr *)ptr)->p_flags;
    case PH_ALIGN:
        return ((Elf64_Phdr *)ptr)->p_align;
    }
    return 0;
}
