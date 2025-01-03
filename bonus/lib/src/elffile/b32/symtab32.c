/*
** EPITECH PROJECT, 2024
** nmobjdump
** File description:
** symtab32
*/

#include "elffile/elffile.h"
#include "elffile/b32/elf32.h"

#include <stdlib.h>
#include <stdio.h>

char *get_symbol_name_b32(elffile_t *elf, void *symbol)
{
    Elf32_Shdr *strtable_hdr = ELFFILE_GET_SECTION_BY_NAME(elf, ".strtab");
    octet_t *strtable;

    if (strtable_hdr == NULL || symbol == NULL) {
        return NULL;
    }
    strtable = ELFFILE_RAW(elf) + strtable_hdr->sh_offset;
    return strtable + ((Elf32_Sym *)symbol)->st_name;
}

void *get_symbol_map_b32(elffile_t *elf)
{
    Elf32_Shdr *symtable_hdr = ELFFILE_GET_SECTION_BY_TYPE(elf, SHT_SYMTAB);
    Elf32_Sym *symtable;

    if (symtable_hdr == NULL)
        return NULL;
    symtable = (Elf32_Sym *)(symtable_hdr->sh_offset + ELFFILE_RAW(elf));
    return symtable;
}
