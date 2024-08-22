# C - Simple Shell

This README.md file contains the necessary files for the Simple Shell project. This project was developed in pairs by José Puertas and Guney Tasdelen.

# Table of Contents

1. [Description](#description)
2. [Operating System:](#operating-system) 
3. [Flowchart](#flowchart)
4. [Features](#features)
5. [Compilation](#compilation)
6. [Usage](#usage)
   - [Interactive Mode](#interactive-mode)
   - [Non-interactive Mode](#non-interactive-mode)
7. [Project Requirements](#project-requirements)
8. [Allowed Functions and System Calls](#allowed-functions-and-system-calls)
9. [Examples](#examples)
10. [Manpage `simple_shell`](#manpage-simple_shell)
11. [Authors](#authors)
12. [References](#references)

## Description

This project involves creating a simple command-line interpreter, similar to the traditional UNIX shell. The objective is to understand the internal workings of shells, learn how to manage processes, system calls, and manipulate the execution environment. The project follows the Betty coding style guidelines and adheres to the specifications to work on Ubuntu 20.04 LTS.

### Operating System:

  - Ubuntu 22.04 LTS (of compatible version)

- **Softwares**:

  - **Visual Studio Code:** Ensure you have the latest version installed (You can find it [here](https://code.visualstudio.com/))

  - **GCC (GNU Compiler Collection):** Requiered for compiling the project. You can install it on your **Visual Code** using this: 
  
```sh
sudo apt-get install gcc
```
  
  - **Betty Style:** A style guide for the C programming language used by the Holberton School and ensuring a well structured and readable code. Ensure you have the Betty linter installed:

```sh
git clone https://github.com/holbertonschool/Betty.git

cd Betty

./install.sh
```

  - **Valgrind:** A tool for memiiry debugging, memory leak detection, and profiling. Install it using:

```sh
sudo apt-get install valgrind
``` 

- **Version Control**

**Git:** Ensure you have Git installed for version control:

```sh
sudo apt-get install git
```
Clone this repository to your local machine:

```bash
git clone https://github.com/Zetrayo/holbertonschool-simple_shell.git
```


## Flowchart
![alt text](SimpleShellFlowchart.jpg)

## Features

- **Execution of simple UNIX commands**: The shell can execute commands like `ls`, `pwd`, `echo`, etc.
- **Interactive Mode**: The shell displays a prompt, waits for the user's input, executes the command, and then displays the prompt again.
- **Non-interactive Mode**: The shell can receive commands via a file or a pipe, execute them, and then terminate.
- **Error Handling**: Errors are managed and displayed similarly to `/bin/sh`.
- **Environment Support**: The shell can execute commands using environment variables such as `PATH`.
- **Built-in Commands**:
  - `exit`: Closes the shell.
  - `env`: Displays the current environment.

## Compilation

To compile the project, use the following command:

```bash
gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh
```

## Usage

### Interactive Mode

To use the shell in interactive mode:

```bash
$ ./hsh
($) /bin/ls
hsh main.c shell.c
($) exit
$
```

### Non-interactive Mode

To use the shell in non-interactive mode:

```bash
$ echo "/bin/ls" | ./hsh
hsh main.c shell.c
$
$ cat test_ls_2 | ./hsh
hsh main.c shell.c test_ls_2
$
```

## Project Requirements

- **Authorized Editors**: `vi`, `vim`, `emacs`.
- **Compilation**: The project will be compiled on Ubuntu 20.04 LTS with `gcc` and the following options: `-Wall -Werror -Wextra -pedantic -std=gnu89`.
- **Code Standards**: The code must follow the Betty coding style.
- **No Memory Leaks**: The shell must be free of memory leaks.
- **Include Guards**: All header files must be protected against multiple inclusions.

## Allowed Functions and System Calls

- **Standard Library Functions (`string.h`)**: All functions.
- **System Calls**: `access`, `chdir`, `close`, `execve`, `fork`, `getpid`, `isatty`, `kill`, `open`, `read`, `wait`, `write`, etc.
- **Memory Management Functions**: `malloc`, `free`.
- **String Manipulation Functions**: `strtok`, etc.
- **I/O Functions**: `printf`, `fprintf`, `vfprintf`, `sprintf`, `fflush`, etc.

## Examples

Interactive mode:

```bash
zetrayo@DESKTOP-UQJR0N7:~/holbertonschool-simple_shell$ ./hsh
($) ls -l
total 136
-rw-r--r-- 1 zetrayo zetrayo   258 Aug 16 15:27 AUTHORS
-rw-r--r-- 1 zetrayo zetrayo  3481 Aug 21 15:00 README.md
-rw-r--r-- 1 zetrayo zetrayo 91172 Aug 16 15:27 SimpleShellFlowchart.jpg
-rw-r--r-- 1 zetrayo zetrayo  2615 Aug 21 11:25 command_interpreter.c
-rw-r--r-- 1 zetrayo zetrayo  2542 Aug 21 10:34 command_reader.c
-rwxr-xr-x 1 zetrayo zetrayo 17392 Aug 22 14:40 hsh
-rw-r--r-- 1 zetrayo zetrayo  2706 Aug 21 15:01 man_1_simple_shell
-rw-r--r-- 1 zetrayo zetrayo  2401 Aug 21 11:22 shell.c
-rw-r--r-- 1 zetrayo zetrayo  1012 Aug 21 11:25 shell.h
($)
```
Non interactive mode:

```bash
zetrayo@DESKTOP-UQJR0N7:~/holbertonschool-simple_shell$ echo "/bin/ls -l" | ./hsh
total 136
-rw-r--r-- 1 zetrayo zetrayo   258 Aug 16 15:27 AUTHORS
-rw-r--r-- 1 zetrayo zetrayo  3481 Aug 21 15:00 README.md
-rw-r--r-- 1 zetrayo zetrayo 91172 Aug 16 15:27 SimpleShellFlowchart.jpg
-rw-r--r-- 1 zetrayo zetrayo  2615 Aug 21 11:25 command_interpreter.c
-rw-r--r-- 1 zetrayo zetrayo  2542 Aug 21 10:34 command_reader.c
-rwxr-xr-x 1 zetrayo zetrayo 17392 Aug 22 14:40 hsh
-rw-r--r-- 1 zetrayo zetrayo  2706 Aug 21 15:01 man_1_simple_shell
-rw-r--r-- 1 zetrayo zetrayo  2401 Aug 21 11:22 shell.c
-rw-r--r-- 1 zetrayo zetrayo  1012 Aug 21 11:25 shell.h
```
## Manpage `simple_shell`

A "Manpage" is short for "Manual Page". This is a command scripted to display the manual page of `simple_shell`, explaining the command and how to use it, while being in bash. Here is how to install it on you local visual code.

**Step 1: Creating the Directory Structure**

First, it's required to create the necessary directories if they don't already exist.

```sh
sudo mkdir -p /usr/local/man/man1
```

**Step 2: Install the manpage**

After creating the directory structure, installing the manpage with `sudo`to ensure to have the necessary permissions:

```sh
sudo cp man_1_simple_shell /usr/local/man/man1/man_1_simple_shell.1
```

Little breakdown about what this all about:

  - **`-o root`:** Specifies the owner of the file (root in this case).

  - **`-m 0644`:** Sets the permissions of the file (readable and writable by the owner, readable by others).

  - **`man_1_simple_shell`:** The source file for the manpage.

  - **`/usr/local/man/man1/man_1_simple_shell.1`:** The destination path for the installed manpage.


**Step 3: Update the manpage database**

You already have a manpage database holding the man of other commands. You need to update it so that `man` can find the new manpage:

```sh
sudo mandb
```

**Step 4: Try it**

```sh
man man_1_simple_shell
```

## Authors

- **Guney TASDELEN** <guney.tasdelen74@gmail.com>
- **José PUERTAS** <josefeliciano.com98@gmail.com>

## References

- **[Unix Shell](https://en.wikipedia.org/wiki/Unix_shell)**
- **[Thompson Shell](https://en.wikipedia.org/wiki/Thompson_shell)**
- **[Ken Thompson](https://en.wikipedia.org/wiki/Ken_Thompson)**
