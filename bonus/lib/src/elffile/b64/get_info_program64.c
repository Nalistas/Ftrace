/*
** PERSONNAL PROJECT 2024
** ftrace
** File description:
** get_info_program
*/

#include "elffile/elffile.h"
#include "elffile/b64/elf64.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

void *get_s_by_name_b64(elffile_t *elf, char const *name)
{
    Elf64_Shdr *hdr = &SHDR64(elf)[EHDR64(elf)->e_shstrndx];
    size_t idx;
    char *str;

    if (elf->section_header == 0) {
        return NULL;
    }
    for (size_t i = 0; i < EHDR64(elf)->e_shnum; ++i) {
        idx = SHDR64(elf)[i].sh_name + hdr->sh_offset;
        str = &(ELFFILE_RAW(elf)[idx]);
        if (strcmp(name, str) == 0) {
            return &SHDR64(elf)[i];
        }
    }
    return NULL;
}

void *get_s_by_type_b64(elffile_t *elf, size_t type)
{
    if (elf->section_header == 0) {
        return NULL;
    }
    for (size_t i = 0; i < EHDR64(elf)->e_shnum; ++i) {
        if (SHDR64(elf)[i].sh_type == type) {
            return &(SHDR64(elf)[i]);
        }
    }
    return NULL;
}
