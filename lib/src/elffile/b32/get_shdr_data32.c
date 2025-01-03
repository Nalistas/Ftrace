/*
** EPITECH PROJECT, 2024
** nmobjdump
** File description:
** get_shdr_data32
*/

#include "elffile/elffile.h"
#include <stdio.h>

static long get_shdr_data32_part2(Elf32_Shdr *shdr, size_t data)
{
    switch (data) {
    case SH_SIZE:
        return shdr->sh_size;
    case SH_LINK:
        return shdr->sh_link;
    case SH_INFO:
        return shdr->sh_info;
    case SH_ADDRALIGN:
        return shdr->sh_addralign;
    case SH_ENTSIZE:
        return shdr->sh_entsize;
    }
    return 0;
}

long get_shdr_data32(void *ptr, size_t data)
{
    Elf32_Shdr *shdr = ptr;

    switch (data) {
    case SH_NAME:
        return shdr->sh_name;
    case SH_TYPE:
        return shdr->sh_type;
    case SH_FLAGS:
        return shdr->sh_flags;
    case SH_ADDR:
        return shdr->sh_addr;
    case SH_OFFSET:
        return shdr->sh_offset;
    default:
        break;
    }
    return get_shdr_data32_part2(shdr, data);
}
