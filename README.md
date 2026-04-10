# Minishell

*This project has been created as part of the 42 curriculum by adores and leramos-.*

## Description

This project implements a fully functional Unix shell, a simplified recreation of bash. The main objective is to understand how a shell works under the hood: reading user input, tokenizing it, parsing it into commands, expanding variables, and finally executing them, all while properly handling signals, pipes, redirections, and environment variables.

## Instructions

To compile the project, run:
```bash
make
```

To launch the shell:
```bash
./minishell
```

Once running, you will be greeted with the prompt:
```
Minishell>
```

From there you can type and execute commands just like in a regular shell.

## Features

### Builtins
The following built-in commands are implemented natively:

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

1. **Lexer** — Tokenizes raw input into a list of typed tokens, handling quotes and special characters
2. **Syntax Validation** — Checks for token errors before attempting to parse
3. **Parser** — Builds a list of command structures from the token list
4. **Expander** — Expands `$VARIABLE` references, `$?` (last exit status), and handles quote stripping
5. **Executor** — Runs the commands, handling pipelines, redirections, heredocs, and builtins

### Redirections
- `>` — Redirect stdout to a file (truncate)
- `>>` — Redirect stdout to a file (append)
- `<` — Redirect stdin from a file
- `<<` — Heredoc: read input until a delimiter is matched

### Pipes
Commands can be chained with `|`, with each command's stdout connected to the next command's stdin.

### Signal Handling
- `Ctrl+C` — Interrupts the current input and displays a new prompt (exit status 130)
- `Ctrl+D` — Exits the shell cleanly
- `Ctrl+\` — Ignored in interactive mode

### Variable Expansion
- `$VAR` — Expands to the value of `VAR` in the environment
- `$?` — Expands to the exit status of the last executed command
- Single quotes `'...'` — Prevent all expansion
- Double quotes `"..."` — Allow variable expansion inside

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

The main resources that contributed to our understanding of this project were discussions with colleagues and working through the project requirements hands-on.

Additional references that were helpful include:

- [Writing a Shell in C - Tutorial](https://brennan.io/2015/01/16/write-a-shell-in-c/)
- [Bash Reference Manual](https://www.gnu.org/software/bash/manual/bash.html)
- [GNU Readline Library](https://tiswww.case.edu/php/chet/readline/rltop.html)

AI tools were used to assist with the writing and structuring of this README file.