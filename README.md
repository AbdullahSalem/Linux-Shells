# NanoShell

A simple Unix-like shell implemented in C using POSIX system calls. NanoShell supports built-in commands, execution of external programs, local variables, environment variables, and variable expansion.

---

## Features

* Built-in commands:

  * `echo`
  * `pwd`
  * `cd`
  * `exit`
* Execute external programs
* Local shell variables
* Environment variables (`export`)
* Variable expansion using `$`
* Searches executables in:

  * `/usr/local/bin`
  * `/usr/bin`
  * `/bin`

---

## Built-in Commands

| Command          | Description                                                                          |
| ---------------- | ------------------------------------------------------------------------------------ |
| `echo [text]`    | Prints text to the terminal.                                                         |
| `pwd`            | Prints the current working directory.                                                |
| `cd [directory]` | Changes the current working directory. If no directory is given, changes to `/home`. |
| `exit`           | Terminates the shell.                                                                |

---

## Local Variables

Create a local variable:

```sh
name=Abdullah
```

Use it:

```sh
echo $name
```

Output:

```text
Abdullah
```

Local variables exist only inside NanoShell.

---

## Environment Variables

Create an environment variable:

```sh
export city=Cairo
```

Use it:

```sh
echo $city
```

Environment variables are created using `setenv()` and are passed to child processes.

---

## Variable Expansion

NanoShell replaces variables beginning with `$` before executing a command.

Example:

```sh
name=John
echo $name
```

Output:

```text
John
```

Environment variables are expanded the same way.

---

## External Commands

If a command is not built into the shell, NanoShell searches for the executable in:

```text
/usr/local/bin/
/usr/bin/
/bin/
```

Examples:

```sh
ls
cat file.txt
mkdir test
```

---

## Compilation

Compile with GCC:

```bash
gcc -Wall -Wextra -std=c11 nanoshell.c -o nanoshell
```

---

## Running

```bash
./nanoshell
```

---

## Example Session

```text
Simple Shell: Enter your command $ pwd
/home/user

Simple Shell: Enter your command $ echo Hello
Hello

Simple Shell: Enter your command $ name=Abdullah

Simple Shell: Enter your command $ echo $name
Abdullah

Simple Shell: Enter your command $ export city=Cairo

Simple Shell: Enter your command $ echo $city
Cairo

Simple Shell: Enter your command $ ls
Desktop  Documents  Downloads

Simple Shell: Enter your command $ cd Documents

Simple Shell: Enter your command $ pwd
/home/user/Documents

Simple Shell: Enter your command $ exit
Good Bye
```

---

## System Calls / Library Functions Used

| Function   | Purpose                                     |
| ---------- | ------------------------------------------- |
| `fork()`   | Creates a child process.                    |
| `execve()` | Executes external programs.                 |
| `wait()`   | Waits for child process termination.        |
| `getcwd()` | Gets the current working directory.         |
| `chdir()`  | Changes the current working directory.      |
| `write()`  | Writes output to the terminal.              |
| `setenv()` | Creates or updates an environment variable. |
| `getenv()` | Retrieves an environment variable.          |
| `fgets()`  | Reads user input.                           |

---

## Limitations

* Supports one variable expansion per command.
* Stores local variables in a fixed-size table.
* Maximum command length is limited by the input buffer.
* Does not support:

  * Pipes (`|`)
  * Input/output redirection (`<`, `>`, `>>`)
  * Background execution (`&`)
  * Wildcards (`*`)
  * Command substitution
  * Aliases
  * Shell scripting

