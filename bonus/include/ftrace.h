/*
** EPITECH PROJECT, 2024
** strace
** File description:
** strace
*/

#include <sys/user.h>
#include <sys/types.h>

#include "process_library.h"

#ifndef STRACE_H_
    #define STRACE_H_


    #define INT80       ((short)0x80cd)
    #define SYSCALL     ((short)0x050f)
    #define SYSENTER    ((short)0x0F34)

    #define IS_INT80(n) ((short)n == INT80)
    #define IS_SYSCALL(n) ((short)n == SYSCALL)
    #define IS_SYSENTER(n) ((short)n == SYSENTER)

    #define IS_KERNELCALL(n) (IS_INT80(n) || IS_SYSCALL(n) || IS_SYSENTER(n))

typedef struct {
    int id;
    char *name;
    int nb_args;
    int retval;
    int arg1t;
    int arg2t;
    int arg3t;
    int arg4t;
    int arg5t;
    int arg6t;
} syscall_t;

typedef struct {
    pid_t child_pid;
    int status;
    struct user_regs_struct regs;
    process_library_t **libs;
    char const *exec_name;
} process_info_t;

typedef void (*display_fct_t)(struct user_regs_struct *, syscall_t *, pid_t);



int launch_ftrace(pid_t child_pid, char const *exec_name);

/////////////////////////////////////////////////////////////////////////:
/// @brief  display the params of the syscall
/// @param  regs
/// @param  syscall
/// @param  childpid
/////////////////////////////////////////////////////////////////////////:
void display_args_detailed(struct user_regs_struct *, syscall_t *, pid_t);

/////////////////////////////////////////////////////////////////////////:
/// @brief get a part of the memory of the child process
/// @param size
/// @param addr
/// @param childpid
/// @return a malloced void* of the size of the param or NULL if error
/////////////////////////////////////////////////////////////////////////:
void *get_sized_param(size_t size, long addr, pid_t childpid);

/////////////////////////////////////////////////////////////////////////:
/// @brief display the param and the return value of the syscall
/// @param current_param
/// @param args_type
/// @param args
/// @param childpid
/////////////////////////////////////////////////////////////////////////:
void display_param(int current_param,
    int const args_type[7],
    long long int const args[7], pid_t childpid);


/////////////////////////////////////////////////////////////////////////:
/// @brief manage the case of execve because the mem is
///    not accessible after the call
/// @param regs
/// @param childpid
/// @return 0 if it is a success, 84 if it is an error
/////////////////////////////////////////////////////////////////////////:
int manage_execve(struct user_regs_struct *regs, pid_t childpid);

enum CALL_RET_CODE {
    CALL_HAPPENED = 0,
    RET_HAPPENED = 1,
    NOTHING_HAPPENED = 2,
    ERROR = 84,
};

/////////////////////////////////////////////////////////////////////////:
/// @brief check if the instruction is a call
/// @param peek1
/// @param peek2
/// @return 1 if it is a call, 0 if it is not
/////////////////////////////////////////////////////////////////////////:
int manage_call_ret(long peek1, process_info_t *process_info);

/////////////////////////////////////////////////////////////////////////////
/// @brief get the correct library
/// @param ftrace
/// @param symbol_address
/// @return the correct library
/////////////////////////////////////////////////////////////////////////////
process_library_t *get_lib(process_info_t *ftrace,
    unsigned long symbol_address);

/////////////////////////////////////////////////////////////////////////////
/// @brief get the name of the function
/// @param ftrace
/// @param addr
/// @return the name of the function
/////////////////////////////////////////////////////////////////////////////
char *get_function_name(process_info_t *ftrace, long addr);

/////////////////////////////////////////////////////////////////////////////
/// @brief annalyze the call e8
/// @param peek1
/// @param proc
/// @return what happened with the call following the @enum CALL_RET_CODE
/////////////////////////////////////////////////////////////////////////////
int check_e8_call(long peek1, process_info_t *proc);

/////////////////////////////////////////////////////////////////////////////
/// @brief annalyze the call ff
/// @param peek1
/// @param proc
/// @return what happened with the call following the @enum CALL_RET_CODE
/////////////////////////////////////////////////////////////////////////////
int check_ff_call(long peek1, process_info_t *proc);

/////////////////////////////////////////////////////////////////////////////
/// @brief get the name of the function
/// @param ftrace
/// @param addr
/// @param elffile
/// @return the name of the function or NULL if not found, BEWARE that the
///     name is malloced
/////////////////////////////////////////////////////////////////////////////
char *find_symbol(process_info_t *ftrace, long addr, int elffile);

/////////////////////////////////////////////////////////////////////////////
/// @brief get the library of the function based on the address
/// @param ftrace
/// @param symbol_address
/// @return the library of the function
/////////////////////////////////////////////////////////////////////////////
process_library_t *find_library_by_address(process_info_t *ftrace,
    unsigned long symbol_address);

/////////////////////////////////////////////////////////////////////////////
/// @brief get the library of the function based on the name
/// @param ftrace
/// @param name
/// @return the library of the function
/////////////////////////////////////////////////////////////////////////////
process_library_t *find_library_by_name(process_info_t *ftrace,
    char const *name);

/////////////////////////////////////////////////////////////////////////////
/// @brief get the name of the function
/// @param addr
/// @param lib_name
/// @return the name of the function
/////////////////////////////////////////////////////////////////////////////
char *create_function_name(long addr, char const *lib_name);



#endif /* !STRACE_H_ */
