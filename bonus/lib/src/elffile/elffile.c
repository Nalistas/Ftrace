/*
** PERSONNAL PROJECT 2024
** ftrace
** File description:
** elf_header
*/

#include "elffile/elffile.h"
#include "elffile/b64/elf64.h"
#include "elffile/b32/elf32.h"

#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <stdio.h>

static int err_msg(char const *msg)
{
    dprintf(2, "elffile lib: %s", msg);
    return KO;
}

static int check_magic_nb(elffile_t *elf)
{
    if (elf->file[EI_DATA] != 1 && elf->file[EI_DATA] != 2) {
        return err_msg("EI_DATA invalid\n");
    }
    if (elf->file[EI_VERSION] != 1) {
        return err_msg("INVALID EI_VERSION\n");
    }
    if (memcmp(elf->file, ELFMAG, SELFMAG) != 0) {
        return err_msg("invalid magic number\n");
    }
    return OK;
}

static int open_elf_file(elffile_t *elf, char const *file)
{
    int fd = open(file, O_RDONLY);
    struct stat s;

    if (fd < 0) {
        return KO;
    }
    if (fstat(fd, &s) < 0)
        return err_msg("fstat failed\n");
    elf->size = s.st_size;
    elf->file = malloc(s.st_size);
    if (elf->file == NULL)
        return err_msg("malloc failed\n");
    if (read(fd, elf->file, s.st_size) < 0)
        return err_msg("failed read\n");
    close(fd);
    return OK;
}

int elffile_delete(elffile_t *elf)
{
    free(elf->namefile);
    free(elf->file);
    return OK;
}

int elffile_init(elffile_t *elf, char const *file)
{
    octet_t mod;

    memset(elf, 0, sizeof(elffile_t));
    if (open_elf_file(elf, file) == KO) {
        return KO;
    }
    if (memcmp(elf->file, ELFMAG, SELFMAG) != 0) {
        return err_msg("invalid magic number\n");
    }
    mod = elf->file[EI_CLASS];
    if (mod == ELFCLASS32) {
        init_elf32(elf);
    } else if (mod == ELFCLASS64) {
        init_elf64(elf);
    } else {
        return KO;
    }
    elf->namefile = strdup(file);
    return check_magic_nb(elf);
}
