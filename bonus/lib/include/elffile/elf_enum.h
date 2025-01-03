/*
** EPITECH PROJECT, 2024
** my_libelf2
** File description:
** elf_enum
*/

#ifndef ELF_ENUM_H_
    #define ELF_ENUM_H_

enum EHDR_DATA_IDS {
    E_TYPE,
    E_MACHINE,
    E_VERSION,
    E_ENTRY,
    E_PHOFF,
    E_SHOFF,
    E_FLAGS,
    E_EHSIZE,
    E_PHENTSIZE,
    E_PHNUM,
    E_SHENTSIZE,
    E_SHNUM,
    E_SHSTRNDX
};

enum SHDR_DATA_IDS {
    SH_NAME,
    SH_TYPE,
    SH_FLAGS,
    SH_ADDR,
    SH_OFFSET,
    SH_SIZE,
    SH_LINK,
    SH_INFO,
    SH_ADDRALIGN,
    SH_ENTSIZE
};

enum SYM_DATA_IDS {
    SYM_NAME,
    SYM_INFO,
    SYM_OTHER,
    SYM_SHNDX,
    SYM_VALUE,
    SYM_SIZE
};

enum PHDR_DATA_IDS {
    PH_TYPE,
    PH_OFFSET,
    PH_VADDR,
    PH_PADDR,
    PH_FILESZ,
    PH_MEMSZ,
    PH_FLAGS,
    PH_ALIGN
};

#endif /* !ELF_ENUM_H_ */
