/*
** PERSONNAL PROJECT 2024
** ftrace
** File description:
** get_info_program
*/

#include "elffile/elffile.h"
#include "elffile/b32/elf32.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

void *get_s_by_name_b32(elffile_t *elf, char const *name)
{
    Elf32_Shdr *hdr = &SHDR32(elf)[EHDR32(elf)->e_shstrndx];
    size_t idx;
    char *str;

    if (elf->section_header == 0) {
        return NULL;
    }
    for (size_t i = 0; i < EHDR32(elf)->e_shnum; ++i) {
        idx = SHDR32(elf)[i].sh_name + hdr->sh_offset;
        str = &(ELFFILE_RAW(elf)[idx]);
        if (strcmp(name, str) == 0) {
            return &SHDR32(elf)[i];
        }
    }
    return NULL;
}

void *get_s_by_type_b32(elffile_t *elf, size_t type)
{
    if (elf->section_header == 0) {
        return NULL;
    }
    for (size_t i = 0; i < EHDR32(elf)->e_shnum; ++i) {
        if (SHDR32(elf)[i].sh_type == type) {
            return &(SHDR32(elf)[i]);
        }
    }
    return NULL;
}
