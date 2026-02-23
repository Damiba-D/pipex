# Pipex

*Created by ddamiba as part of the 42 school curriculum*

## Description

Pipex is a Unix system programming project that recreates the behavior of shell pipes. The program mimics the shell pipe operator (`|`) by executing two or more commands in sequence, passing the output of one command as input to the next through pipes. This project provides deep insight into process creation, file descriptors, inter-process communication, and Unix system calls.

The program handles both mandatory functionality (two commands with input/output files) and bonus features including multiple pipes (chaining multiple commands) and here_doc mode for reading from stdin until a delimiter is encountered.

## Features

- **Basic Piping**: Executes two commands with pipe between them
- **Multiple Pipes**: Supports chaining of multiple commands (bonus)
- **Here_doc Mode**: Reads from stdin until delimiter is reached (bonus)
- **Command Path Resolution**: Automatically finds commands in PATH
- **Error Handling**: Comprehensive error messages for invalid files, commands, or arguments
- **Robust Argument Parsing**: Custom argument splitter handling quotes and escapes
- **Exit Code Propagation**: Returns the exit status of the last command

## Compilation

```bash
make        # Compile the project
make clean  # Remove object files
make fclean # Remove object files and executable
make re     # Recompile from scratch
```

## Execution

### Basic Usage (Mandatory)
```bash
./pipex infile "cmd1" "cmd2" outfile
```

This behaves like the shell command:
```bash
< infile cmd1 | cmd2 > outfile
```

**Examples:**
```bash
./pipex infile "ls -l" "wc -l" outfile
# Equivalent to: < infile ls -l | wc -l > outfile

./pipex infile "grep hello" "wc -w" outfile
# Equivalent to: < infile grep hello | wc -w > outfile

./pipex infile "cat" "grep 42" outfile
# Equivalent to: < infile cat | grep 42 > outfile
```

### Multiple Pipes (Bonus)
```bash
./pipex infile "cmd1" "cmd2" "cmd3" ... "cmdN" outfile
```

**Examples:**
```bash
./pipex infile "cat" "grep keyword" "wc -l" outfile
# Equivalent to: < infile cat | grep keyword | wc -l > outfile

./pipex infile "ls -l" "grep .c" "wc -l" "cat" outfile
# Chains 4 commands together
```

### Here_doc Mode (Bonus)
```bash
./pipex here_doc LIMITER "cmd1" "cmd2" outfile
```

This behaves like:
```bash
cmd1 << LIMITER | cmd2 >> outfile
```

**Examples:**
```bash
./pipex here_doc EOF "grep hello" "wc -l" outfile
# Type input lines, then type EOF to finish
# Output is appended to outfile

./pipex here_doc STOP "cat" "grep 42" outfile
# Reads from stdin until STOP is encountered
```

## Project Structure

```
pipex/
├── pipex.c              # Main program logic and parsing
├── pipex.h              # Header file with structures and prototypes
├── cmd1.c               # First command execution (reads from infile)
├── cmd2.c               # Last command execution (writes to outfile)
├── cmdmid.c             # Middle command execution (bonus)
├── cmdutils.c           # Command path resolution and execution utilities
├── gen_utils.c          # General utility functions
├── arg_split/           # Custom argument parser
│   ├── arg_split.c      # Main parsing logic with quote handling
│   ├── arg_split.h      # Argument parser header
│   ├── copying.c        # Token copying functions
│   └── counting.c       # Argument counting functions
├── libft/               # Personal C library
│   ├── *.c              # Standard library reimplementations
│   ├── ft_printf/       # Custom printf implementation
│   └── get_next_line/   # Line reading function (for here_doc)
└── Makefile             # Compilation rules
```

## Technical Details

### Core Concepts

**Pipes**: Unix mechanism for inter-process communication. Creates a unidirectional data channel with a read end and write end.

**Fork**: System call that creates a child process, duplicating the parent's memory space.

**Execve**: System call that replaces the current process image with a new program.

**File Descriptors**: Integer references to open files/streams. Standard: 0 (stdin), 1 (stdout), 2 (stderr).

**Dup2**: System call to duplicate file descriptors, used to redirect stdin/stdout.

### Implementation Strategy

1. **Argument Parsing**: Custom splitter handles quotes and escapes in command arguments
2. **Pipe Creation**: Creates pipes for communication between processes
3. **Process Forking**: Spawns child processes for each command
4. **File Descriptor Manipulation**: Redirects stdin/stdout using dup2
5. **Command Execution**: Resolves command paths and executes with execve
6. **Waiting**: Parent waits for all children and propagates final exit code

### Argument Parser

The custom `arg_split` function handles:
- Single quotes (preserves literal characters)
- Backslash escapes outside quotes
- Multiple spaces between arguments
- Empty strings in quotes
- Unmatched quote detection

### Error Handling

The program handles various error conditions:
- Invalid number of arguments
- File access errors (permission denied, file not found)
- Command not found or not executable
- Pipe creation failures
- Fork failures
- Memory allocation failures
- Invalid command arguments (unmatched quotes)

## Requirements

- **Operating System**: Linux/Unix
- **Compiler**: GCC with flags `-Wall -Wextra -Werror`
- **Libraries**: Standard C library
- **System Calls**: `open`, `close`, `read`, `write`, `pipe`, `fork`, `dup2`, `execve`, `waitpid`, `malloc`, `free`, `perror`, `access`

## Resources

### Primary Learning Source
- **Unix Processes in C** by CodeVault (YouTube playlist): https://www.youtube.com/playlist?list=PLfqABt5AS4FkW5mOn2Tn9ZZLLDwA3kZUY
  - Comprehensive tutorial series covering fork, exec, pipes, and process management
  - Practical examples and detailed explanations of Unix system calls
  - Essential viewing for understanding process control and IPC

### Additional Resources
- `man 2 pipe` - Pipe system call documentation
- `man 2 fork` - Fork system call documentation  
- `man 2 execve` - Execve system call documentation
- `man 2 dup2` - Dup2 system call documentation
- `man 2 waitpid` - Waitpid system call documentation
- `man 3 exit` - Exit function documentation

### AI Usage Disclosure
Limited use of AI for logic verification on specific implementation details:
- Checking the correct sequencing of pipe operations and file descriptor management
- Verifying proper parent-child process synchronization logic
- Confirming edge cases in command execution and error handling
- **No AI-generated code** - all implementation written manually after studying the CodeVault tutorials

## Notes

- Commands are resolved using the `PATH` environment variable
- If a command is not in PATH, absolute or relative paths can be used
- The program properly handles process cleanup and file descriptor closure
- Exit codes match the behavior of bash pipelines
- Here_doc mode appends to the output file instead of truncating
- Memory leaks are prevented through careful resource management
- Child processes are properly reaped to avoid zombies

## Author

ddamiba - 42 Lisboa
