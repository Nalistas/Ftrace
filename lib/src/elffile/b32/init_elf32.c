/*
** PERSONNAL PROJECT 2024
** ftrace
** File description:
** init_struct_32
*/

#include "elffile/elffile.h"
#include "elffile/b32/elf32.h"
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

static int init_strtab_b32(elffile_t *elf)
{
    Elf32_Shdr *shdr_strtab = &SHDR32(elf)[EHDR32(elf)->e_shstrndx];

    elf->string_table = elf->file + shdr_strtab->sh_offset;
    return OK;
}

int init_elf32(elffile_t *elf)
{
    elf->get_section_by_type = &get_s_by_type_b32;
    elf->get_section_by_name = &get_s_by_name_b32;
    elf->get_symbol_map = &get_symbol_map_b32;
    elf->get_symbol_name = &get_symbol_name_b32;
    elf->create_shdr_iter = &create_shdr_iter_b32;
    elf->create_phdr_iter = &create_phdr_iter_b32;
    elf->create_symtab_iter = &create_symtab_iter_b32;
    elf->get_phdr_data = &get_phdr_data32;
    elf->get_shdr_data = &get_shdr_data32;
    elf->get_ehdr_data = &get_ehdr_data32;
    elf->get_sym_data = &get_sym_data32;
    elf->program_header = ELFFILE_RAW(elf) + EHDR32(elf)->e_phoff;
    elf->section_header = ELFFILE_RAW(elf) + EHDR32(elf)->e_shoff;
    elf->symbol_table = get_symbol_map_b32(elf);
    init_strtab_b32(elf);
    return OK;
}
