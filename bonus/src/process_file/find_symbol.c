/*
** PERSONNAL PROJECT 2024
** ftrace
** File description:
** find_symbol
*/

#include "ftrace.h"
#include "myelf.h"

#include <sys/ptrace.h>
#include <string.h>
#include <stddef.h>
#include <elf.h>

static char *find_local_symbol(long addr, int elffile)
{
    long offset;
    char const *ptr = myelf_get_symstring_table(elffile);

    for (int it = myelf_create_sym_iterator(elffile);
        !myelf_iterator_end(it); myelf_iterator_next(it)) {
        offset = myelf_get_iterator_info(it, SYM_VALUE);
        if (offset == addr) {
            return strdup(ptr + myelf_get_iterator_info(it, SYM_NAME));
        }
    }
    return NULL;
}

static long calculate_dynamic_offset(process_info_t *ftrace,
    unsigned long call_addr)
{
    long jmpoffset = 0;
    unsigned long offset = 0;
    long value = ptrace(PTRACE_PEEKTEXT, ftrace->child_pid, call_addr + 2);

    if (value == -1)
        return -1;
    jmpoffset = value & 0xFFFFFFFF;
    offset = call_addr + 6 + jmpoffset;
    return offset;
}

static char *char_getname(int elffile, Elf64_Rela *rela)
{
    long dynamic_symtab = -1;
    long counter = 0;
    Elf64_Shdr const *shdrtab = (void const *)myelf_get_shdrtab_ptr(elffile);
    Elf64_Sym *sym;
    long sh_link;
    char const *strtab;

    for (int it2 = myelf_create_shdr_iterator(elffile);
        !myelf_iterator_end(it2); myelf_iterator_next(it2)) {
        if (myelf_get_iterator_info(it2, SH_TYPE) == SHT_DYNSYM)
            dynamic_symtab = counter;
        counter += 1;
    }
    if (dynamic_symtab == -1)
        return NULL;
    sh_link = shdrtab[dynamic_symtab].sh_link;
    strtab = shdrtab[sh_link].sh_offset + myelf_get_raw_file(elffile);
    sym = &((Elf64_Sym *)(shdrtab[dynamic_symtab].sh_offset
        + myelf_get_raw_file(elffile)))[ELF64_R_SYM(rela->r_info)];
    return strdup(strtab + sym->st_name);
}

static char *get_name_in_sym(int elffile, __attribute__((unused)) long addr,
    unsigned long dynamic_offset, int iterator)
{
    char const *ptr = myelf_get_raw_file(elffile);
    Elf64_Rela *rela = (Elf64_Rela *)(ptr +
        myelf_get_iterator_info(iterator, SH_OFFSET));
    Elf64_Sym *symtab = myelf_get_symtab_ptr(elffile);
    long size = myelf_get_iterator_info(iterator, SH_SIZE);
    long count = size / sizeof(Elf64_Rela);
    long type = myelf_get_iterator_info(iterator, SH_TYPE);

    if (type != SHT_RELA || rela == NULL || size == 0 || symtab == NULL) {
        return NULL;
    }
    for (int i = 0; i < count; i++) {
        if (rela[i].r_offset == dynamic_offset) {
            return char_getname(elffile, &rela[i]);
        }
    }
    return NULL;
}

static char *find_dynamic_symbol(int elffile, long addr,
    unsigned long dynamic_offset)
{
    char *name = NULL;

    for (int it = myelf_create_shdr_iterator(elffile);
        !myelf_iterator_end(it); myelf_iterator_next(it)) {
            name = get_name_in_sym(elffile, addr, dynamic_offset, it);
            if (name) {
                return name;
            }
    }
    return NULL;
}

char *find_symbol(process_info_t *ftrace, long addr, int elffile)
{
    char *f_name = NULL;
    long dynamic_offset = 0;
    unsigned long starting_addr =
        find_library_by_name(ftrace,
        myelf_get_file_name(elffile))->start_addr;

    f_name = find_local_symbol(addr, elffile);
    if (f_name)
        return f_name;
    dynamic_offset = calculate_dynamic_offset(ftrace, addr);
    if (dynamic_offset == -1)
        return NULL;
    f_name = find_dynamic_symbol(elffile, addr, dynamic_offset);
    if (f_name)
        return f_name;
    f_name = find_local_symbol(addr - starting_addr, elffile);
    if (f_name) {
        return f_name;
    }
    return NULL;
}
