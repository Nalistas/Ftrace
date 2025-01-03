/*
** PERSONNAL PROJECT 2024
** ftrace
** File description:
** ftrace
*/

#include "elffile/elffile.h"
#include <elf.h>

#ifndef ELF64_H_
    #define ELF64_H_

    #define PHDR64(elf) (((Elf64_Phdr*)elf->program_header))
    #define SHDR64(elf) (((Elf64_Shdr*)elf->section_header))
    #define EHDR64(elf) (((Elf64_Ehdr*)elf->file))

/**
 * @brief Initializes the elf64 struct
 * @param elf The elf file struct to initialize
 * @return OK if the initialization succeeded
 */
int init_elf64(elffile_t *elf);

/**
 * @brief Gets a section header by its type
 * @param elf The elf file struct
 * @param type The type of the section header
 * @return A pointer on the section header if found, otherwise NULL
 */
void *get_s_by_type_b64(elffile_t *elf, size_t type);

/**
 * @brief Gets a section header by its name
 * @param elf The elf file struct
 * @param name The name of the section header
 * @return A pointer on the section header if found, otherwise NULL
 */
void *get_s_by_name_b64(elffile_t *elf, char const *name);

/**
 * @brief Gets the symbol map of the elf file
 * @param elf The elf file struct
 * @return A pointer on the symbol map
 */
void *get_symbol_map_b64(elffile_t *elf);

/**
 * @brief Gets the name of a symbol
 * @param elf The elf file struct
 * @param symbol The symbol to get the name from
 * @return The name of the symbol
 */
char *get_symbol_name_b64(elffile_t *elf, void *symbol);

/**
 * @brief Initializes an iterator on the section header
 * @param elf The elf file struct
 * @return An iterator on the section header
 */
elf_tab_it_t create_shdr_iter_b64(elffile_t *elf);

/**
 * @brief Initializes an iterator on the program header
 * @param elf The elf file struct
 * @return An iterator on the program header
 */
elf_tab_it_t create_phdr_iter_b64(elffile_t *elf);

/**
 * @brief Initializes an iterator on the symbol table
 * @param elf The elf file struct
 * @return An iterator on the symbol table
 */
elf_tab_it_t create_symtab_iter_b64(elffile_t *elf);

/**
 * @brief Gets data from a section header
 * @param ptr A pointer on a section header
 * @param data The data to get from the section header
 * @return The data
 */
long get_shdr_data64(void *ptr, size_t data);

/**
 * @brief Gets data from the elf file header
 * @param elf The elf file struct
 * @param data The data to get from the elf file header
 * @return The data
 */
long get_ehdr_data64(elffile_t *elf, size_t data);

/**
 * @brief Gets data from a program header
 * @param ptr A pointer on a program header
 * @param data The data to get from the program header
 * @return The data
 */
long get_phdr_data64(void *ptr, size_t data);

/**
 * @brief Gets data from a symbol
 * @param ptr A pointer on a symbol
 * @param data The data to get from the symbol
 * @return The data
 */
long get_sym_data64(void *ptr, size_t data);


#endif /* !ELF64_H_ */
