/*
** EPITECH PROJECT, 2024
** nmobjdump
** File description:
** elf32
*/

#include "elffile/elffile.h"
#include <elf.h>

#ifndef ELF32_H_
    #define ELF32_H_

    #define PHDR32(elf) (((Elf32_Phdr*)elf->program_header))
    #define SHDR32(elf) (((Elf32_Shdr*)elf->section_header))
    #define EHDR32(elf) (((Elf32_Ehdr*)elf->file))

/**
 * @brief Initializes the elf32 struct
 * @param elf The elf file struct to initialize
 * @return OK if the initialization succeeded
 */
int init_elf32(elffile_t *elf);

/**
 * @brief Gets a section header by its type
 * @param elf The elf file struct
 * @param type The type of the section header
 * @return A pointer on the section header if found, otherwise NULL
 */
void *get_s_by_type_b32(elffile_t *elf, size_t type);

/**
 * @brief Gets a section header by its name
 * @param elf The elf file struct
 * @param name The name of the section header
 * @return A pointer on the section header if found, otherwise NULL
 */
void *get_s_by_name_b32(elffile_t *elf, char const *name);

/**
 * @brief Gets the symbol map of the elf file
 * @param elf The elf file struct
 * @return A pointer on the symbol map
 */
void *get_symbol_map_b32(elffile_t *elf);

/**
 * @brief Gets the name of a symbol
 * @param elf The elf file struct
 * @param symbol A pointer on a symbol in the symbol map
 * @return The name of the symbol
 */
char *get_symbol_name_b32(elffile_t *elf, void *symbol);

/**
 * @brief Initializes an iterator on the section headers
 * @param elf The elf file struct
 * @return An iterator on the section headers
 */
elf_tab_it_t create_shdr_iter_b32(elffile_t *elf);

/**
 * @brief Initializes an iterator on the program headers
 * @param elf The elf file struct
 * @return An iterator on the program headers
 */
elf_tab_it_t create_phdr_iter_b32(elffile_t *elf);

/**
 * @brief Initializes an iterator on the symbols
 * @param elf The elf file struct
 * @return An iterator on the symbols
 */
elf_tab_it_t create_symtab_iter_b32(elffile_t *elf);

/**
 * @brief Gets the data contained in a section header
 * @param ptr A pointer on a section header
 * @param data The type of data to get
 * @return The data contained in the section header
 */
long get_shdr_data32(void *ptr, size_t data);

/**
 * @brief Gets the data contained in the ELF header
 * @param elf The elf file struct
 * @param data The type of data to get
 * @return The data contained in the ELF header
 */
long get_ehdr_data32(elffile_t *elf, size_t data);

/**
 * @brief Gets the data contained in a program header
 * @param ptr A pointer on a program header
 * @param data The type of data to get
 * @return The data contained in the program header
 */
long get_phdr_data32(void *ptr, size_t data);

/**
 * @brief Gets the data contained in a symbol
 * @param ptr A pointer on a symbol
 * @param data The type of data to get
 * @return The data contained in the symbol
 */
long get_sym_data32(void *ptr, size_t data);


#endif /* !ELF32_H_ */
