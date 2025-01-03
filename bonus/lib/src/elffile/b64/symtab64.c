/*
** EPITECH PROJECT, 2024
** nmobjdump
** File description:
** symtab64
*/

#include "elffile/b64/elf64.h"
#include "elffile/elffile.h"

#include <stdlib.h>
#include <stdio.h>

char *get_symbol_name_b64(elffile_t *elf, void *symbol)
{
    Elf64_Shdr *strtable_hdr = ELFFILE_GET_SECTION_BY_NAME(elf, ".strtab");
    octet_t *strtable;

    if (strtable_hdr == NULL || symbol == NULL) {
        return NULL;
    }
    strtable = ELFFILE_RAW(elf) + strtable_hdr->sh_offset;
    return strtable + ((Elf64_Sym *)symbol)->st_name;
}

void *get_symbol_map_b64(elffile_t *elf)
{
    Elf64_Shdr *symtable_hdr = ELFFILE_GET_SECTION_BY_TYPE(elf, SHT_SYMTAB);
    Elf64_Sym *symtable;

    if (symtable_hdr == NULL)
        return NULL;
    symtable = (Elf64_Sym *)(symtable_hdr->sh_offset + ELFFILE_RAW(elf));
    return symtable;
}
