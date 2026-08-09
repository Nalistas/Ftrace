# ftrace
Program tracing tool made in C for the System Programming project of Epitech (2nd year).

## About
ftrace is a re-implementation of a subset of `ltrace`/`strace`. It traces the library calls and syscalls made by a given program during its execution, and displays them in real time, similarly to the original Linux tools.

## Current State
✅ Project completed — passed 80%+ of the Epitech test suite (Moulinette).

- Traces both library calls and syscalls of a dynamically linked ELF executable on Linux x86-64.
- Uses `ptrace` to intercept calls at runtime.
- Output format mimics `ltrace`'s: call name, arguments, and return value.
- The traced program must be called with an **absolute path** (e.g. `/bin/ls`, not `ls`).

## How it works
1. The target program is launched as a child process using `fork` and `ptrace(PTRACE_TRACEME, ...)`.
2. The parent process intercepts calls via `ptrace`, stopping the child at each relevant breakpoint.
3. Register values (following the x86-64 calling convention) are read to reconstruct function arguments and return values.
4. Symbols are resolved from the binary's dynamic symbol table (PLT/GOT) to identify which function is being called.
5. Each intercepted call is formatted and printed to stdout as it happens.

## Usage
```bash
make
./ftrace /bin/ls -la
```

## Bonus
The `bonus/` directory contains a variant of the project that, instead of (or in addition to) printing calls to stdout, generates a `graph.xml` file describing the function call graph. This file can then be passed through a Python script to render an image visualizing the call graph.

```bash
cd bonus
make
./ftrace /bin/ls -la
python3 generate_graph.py graph.xml
```

## Notes
- This project is considered finished and is not planned to be extended further.
- Static binaries and architectures other than x86-64 are not supported.

## Context
This project was developed during my 2nd year at Epitech, as part of the System Programming module, with the goal of understanding how low-level tracing tools work — process control via `ptrace`, ELF symbol resolution, and the x86-64 calling convention.
