# Minishell

*This project has been created as part of the 42 curriculum by adores and leramos-.*

## Description

This project represents a simplified recreation of bash. The main objective is to understand how a shell works: reading user input, tokenizing it, parsing it into commands, expanding variables, and finally executing them, all while properly handling signals, pipes, redirections, and environment variables.

## Instructions

To compile the project, run:
```bash
make
```

To launch the shell:
```bash
./minishell
```

From there you can type and execute commands just like in a regular shell.

## Features

### Builtins
The following built-in commands are implemented:

| Command | Description |
|---------|-------------|
| `echo [-n]` | Print text to standard output. `-n` suppresses the trailing newline |
| `cd [path]` | Change the current directory. Supports `~` (home) and `-` (previous directory) |
| `pwd` | Print the current working directory |
| `env` | Display all environment variables |
| `export [var=value]` | Set or display exported environment variables |
| `unset [var]` | Remove an environment variable |
| `exit [status]` | Exit the shell with an optional exit code |

### Execution Pipeline
Each input goes through the following stages:

1. **Lexer** - Tokenizes raw input into a list of typed tokens, handling quotes and special characters. Checks if they are valid.
2. **Parser** - Builds a list of command structures from the token list
3. **Expander** - Expands `$VARIABLE` references, `$?` (last exit status), and handles quote stripping
4. **Executor** - Runs the commands, handling pipelines, redirections, heredocs, and builtins

### Redirections
- `>` - Redirect stdout to a file
- `>>` - Redirect stdout to a file (append)
- `<` - Redirect stdin from a file
- `<<` - Heredoc: read input until a delimiter is matched

### Pipes
Commands can be used with `|`, with each command's stdout connected to the next command's stdin.

### Signal Handling
- `Ctrl+C` - Interrupts the current input and displays a new prompt
- `Ctrl+D` - Exits the shell
- `Ctrl+\` - Ignored in interactive mode

### Variable Expansion
- `$VAR` - Expands to the value of `VAR` in the environment
- `$?` - Expands to the exit status of the last executed command
- Single quotes `'...'` - Prevent all expansion
- Double quotes `"..."` - Allow variable expansion inside

## Expected Output

```
Minishell> echo hello world
hello world
Minishell> export NAME=42
Minishell> echo "Hello $NAME"
Hello 42
Minishell> ls | grep .c | wc -l
      5
Minishell> cat << EOF
> line one
> EOF
line one
Minishell> exit
```

## Resources

The main resources that contributed to our understanding of this project were discussions with colleagues and some additional references:

- [Ali Naqvi - Writing a bash-like shell in C](https://www.alimnaqvi.com/blog/minishell)
- [Bash Reference Manual](https://www.gnu.org/software/bash/manual/bash.html)
- [Writing Your Own Shell](https://www.cs.purdue.edu/homes/grr/SystemsProgrammingBook/Book/Chapter5-WritingYourOwnShell.pdf)

AI tools were used to assist with the writing and structuring of this README file and to help debug some bugs.