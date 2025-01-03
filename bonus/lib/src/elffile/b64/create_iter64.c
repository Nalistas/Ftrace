/*
** EPITECH PROJECT, 2024
** my_libelf2
** File description:
** create_iter64
*/

#include "elffile/elffile.h"
#include "elffile/b64/elf64.h"

elf_tab_it_t create_shdr_iter_b64(elffile_t *elf)
{
    elf_tab_it_t it;

    it.i = 0;
    if (elf->section_header == NULL) {
        it.nmem = 0;
        return it;
    }
    it.nmem = EHDR64(elf)->e_shnum;
    it.size_hdr = sizeof(Elf64_Shdr);
    it.hdr = elf->section_header;
    return it;
}

elf_tab_it_t create_phdr_iter_b64(elffile_t *elf)
{
    elf_tab_it_t it;

    it.i = 0;
    if (elf->program_header == NULL) {
        it.nmem = 0;
        return it;
    }
    it.nmem = EHDR64(elf)->e_phnum;
    it.size_hdr = sizeof(Elf64_Phdr);
    it.hdr = elf->program_header;
    return it;
}

elf_tab_it_t create_symtab_iter_b64(elffile_t *elf)
{
    elf_tab_it_t it;
    Elf64_Shdr *symtable_hdr = ELFFILE_GET_SECTION_BY_TYPE(elf, SHT_SYMTAB);

    it.i = 0;
    if (elf->symbol_table == NULL) {
        it.nmem = 0;
        return it;
    }
    it.nmem = symtable_hdr->sh_size / sizeof(Elf64_Sym);
    it.size_hdr = sizeof(Elf64_Sym);
    it.hdr = elf->symbol_table;
    return it;
}
