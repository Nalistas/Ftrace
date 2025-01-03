/*
** EPITECH PROJECT, 2024
** nmobjdump
** File description:
** elf_full_format
*/

#include <elf.h>
#include <stdlib.h>

#ifndef ELF_FULL_FORMAT_H_
    #define ELF_FULL_FORMAT_H_

    #include "elffile/elf_enum.h"

    #define KO 84
    #define OK 0

typedef char octet_t;

typedef struct elf_hdr_it {
    size_t size_hdr;
    size_t nmem;
    size_t i;
    void *hdr;
} elf_tab_it_t;

typedef struct elf {
    octet_t *file;
    size_t size;
    char *namefile;
    octet_t *program_header;
    octet_t *section_header;
    octet_t *symbol_table;
    octet_t *dynsym_table;
    octet_t *string_table;

    void *(*get_section_by_type)(struct elf *, size_t); // DONE
    void *(*get_section_by_name)(struct elf *, char const *); // DONE

    void *(*get_segment_by_type)(struct elf *, size_t);

    void *(*get_symbol_map)(struct elf *); // DONE
    char *(*get_symbol_name)(struct elf *, void *); // DONE

    long (*get_sym_data)(void *, size_t id_data); // DONE
    long (*get_phdr_data)(void *, size_t id_data); // DONE
    long (*get_shdr_data)(void *, size_t id_data); // DONE
    long (*get_symdyn_data)(struct elf *, size_t id_data);
    long (*get_ehdr_data)(struct elf *, size_t id_data); // DONE

    elf_tab_it_t (*create_shdr_iter)(struct elf *); // DONE
    elf_tab_it_t (*create_phdr_iter)(struct elf *); // DONE
    elf_tab_it_t (*create_symtab_iter)(struct elf *); // DONE
    elf_tab_it_t (*create_dynsym_iter)(struct elf *);
} elffile_t;


int elffile_init(elffile_t *elf, char const *filename);
int elffile_delete(elffile_t *elf);


/* Get a pointer to the file content                           */
/*                                                             */
/* ex: octet_t *data = ELFFILE_RAW(elf);                          */
    #define ELFFILE_RAW(elf) ((octet_t *)(elf)->file)

/* Get a pointer to the section header of type `type'          */
/*                                                             */
/* ex: void *shdr = GET_SECTION_BY_TYPE(elf, SHT_SYMTAB);      */
    #define ELFFILE_GET_SECTION_BY_TYPE(f, t) (f->get_section_by_type(f, t))

/* Get a pointer to the section header named `name'            */
/*                                                             */
/* ex: void *shdr = GET_SECTION_BY_NAME(elf, ".symtab");       */
    #define ELFFILE_GET_SECTION_BY_NAME(f, n) (f->get_section_by_name(f, n))

/* Get a pointer to the program header of type `type'          */
/*                                                             */
/* ex: void *phdr = GET_SEGMENT_BY_TYPE(elf, PT_LOAD);        */
    #define ELFFILE_GET_SEGMENT_BY_TYPE(f, t) (f->get_segment_by_type(f, t))

/* Get a pointer to the symbol map (linked list of symbols)    */
/*                                                             */
/* ex: void *sym_map = GET_SYM_MAP(elf);                       */
    #define ELFFILE_GET_SYM_MAP(f) (f->get_symbol_map(f))

/* Get the name of a symbol                                    */
/*                                                             */
/* ex: char *sym_name = GET_SYM_NAME(elf, sym);                */
    #define ELFFILE_GET_SYM_NAME(f, sym) (f->get_symbol_name(f, sym))

/* Get the module type (32-bit or 64-bit)                      */
/*                                                             */
/* ex: octet_t is_64bit = GET_MOD32X64(elf);                   */
    #define ELFFILE_GET_MOD32X64(f) (ELFFILE_RAW(f)[EI_CLASS])

/* Iterate over the section headers                            */
/*                                                             */
/* ex: elf_tab_it_t iter = ELF_SHDR_ITER(elf);                 */
/*     while (!ELF_ITER_END(iter)) {                           */
/*         Elf64_Shdr *hdr = ELF_ITER_GET(iter);               */
/*         ...                                                 */
/*         ELF_ITER_INC(iter);                                 */
/*     }                                                       */
    #define ELFFILE_SHDR_ITER(elf) (elf->create_shdr_iter(elf))

/* Iterate over the program headers                            */
/*                                                             */
/* ex: elf_tab_it_t iter = ELF_PHDR_ITER(elf);                 */
/*     while (!ELF_ITER_END(iter)) {                           */
/*         Elf64_Shdr *hdr = ELF_ITER_GET(iter);               */
/*         ...                                                 */
/*         ELF_ITER_INC(iter);                                 */
/*     }                                                       */
    #define ELFFILE_PHDR_ITER(elf) (elf->create_shdr_iter(elf))

/* Iterate over the symbol table                               */
/*                                                             */
/* ex: elf_tab_it_t iter = ELF_SYM_ITER(elf);                  */
/*     while (!ELF_ITER_END(iter)) {                           */
/*         Elf64_Sym *sym = ELF_ITER_GET(iter);                */
/*         ...                                                 */
/*         ELF_ITER_INC(iter);                                 */
/*     }                                                       */
    #define ELFFILE_SYM_ITER(f) (f->create_symtab_iter(f))

/* Increment the iterator                                      */
/*                                                             */
/* ex: ELF_ITER_INC(iter);                                     */
    #define ELFFILE_ITER_INC(iter) (iter.i += 1)

/* Check if the iterator has reached the end                   */
/*                                                             */
/* ex: if (ELF_ITER_END(iter)) {                               */
/*         break;                                              */
/*     }                                                       */
    #define ELFFILE_ITER_END(iter) (iter.i >= iter.nmem)

/* Get the current section header                              */
/*                                                             */
/* ex: Elf64_Shdr *hdr = ELF_ITER_GET(iter);                   */
    #define ELFFILE_ITER_GET(iter) (iter.hdr + (iter.i * iter.size_hdr))

/* Get the data of a section header                            */
/*                                                             */
/* ex: long data = GET_SHDR_DATA(elf, shdr, SH_ADDR);          */
    #define ELFFILE_GET_SHDR_DATA(f, shdr, d) (f->get_shdr_data(shdr, d))

/* Get the data of the ELF header                              */
/*                                                             */
/* ex: long data = GET_EHDR_DATA(elf, E_SHSTRNDX);             */
    #define ELFFILE_GET_EHDR_DATA(f, data) (f->get_ehdr_data(f, data))

/* Get the data of a symbol                                    */
/*                                                             */
/* ex: long address = GET_SYM_DATA(elf, sym, ST_VALUE);        */
    #define ELFFILE_GET_SYM_DATA(f, sym, d) (f->get_sym_data(sym, d))

/* Get the data of a program header                            */
/*                                                             */
/* ex: long address = GET_PHDR_DATA(elf, phdr, P_VADDR);       */
    #define ELFFILE_GET_PHDR_DATA(f, phdr, d) (f->get_phdr_data(phdr, d))



#endif /* !ELF_FULL_FORMAT_H_ */
