/*
** EPITECH PROJECT, 2024
** nmobjdump
** File description:
** get_ehdr_data64
*/

#include "elffile/elffile.h"

static long get_ehdr_data64_part2(Elf64_Ehdr *ehdr, size_t data)
{
    switch (data) {
    case E_FLAGS:
        return ehdr->e_flags;
    case E_EHSIZE:
        return ehdr->e_ehsize;
    case E_PHENTSIZE:
        return ehdr->e_phentsize;
    case E_PHNUM:
        return ehdr->e_phnum;
    case E_SHENTSIZE:
        return ehdr->e_shentsize;
    case E_SHNUM:
        return ehdr->e_shnum;
    case E_SHSTRNDX:
        return ehdr->e_shstrndx;
    default:
        return 0;
    }
}

long get_ehdr_data64(elffile_t *elf, size_t data)
{
    Elf64_Ehdr *ehdr = (Elf64_Ehdr *)elf->file;

    switch (data) {
    case E_TYPE:
        return ehdr->e_type;
    case E_MACHINE:
        return ehdr->e_machine;
    case E_VERSION:
        return ehdr->e_version;
    case E_ENTRY:
        return ehdr->e_entry;
    case E_PHOFF:
        return ehdr->e_phoff;
    case E_SHOFF:
        return ehdr->e_shoff;
    default:
        break;
    }
    return get_ehdr_data64_part2(ehdr, data);
}
