# Holberton Shell

This project is meant to create a custom "Shell" which is the interface executing commands 
entered by the administrator and making system calls to the kernel.

## Requirements

### Compilation
The compilation command used is:
`gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh`
which means that this project will include only .c files.

### To Know
- the version of Ubuntu will be Ubuntu 20.04 LTS
- the code have to respect Betty style
- forbid to use mor than 5 functions per file
- all files will have ["shell.h"](./shell.h) as the header file ("#include shell.h")
- The shell should not have any memory leaks
- No more than 5 functions per file

### Authorized functions
- all functions from string.h
- access (man 2 access)
- chdir (man 2 chdir)
- close (man 2 close)
- closedir (man 3 closedir)
- execve (man 2 execve)
- exit (man 3 exit)
- _exit (man 2 _exit)
- fflush (man 3 fflush)
- fork (man 2 fork)
- free (man 3 free)
- getcwd (man 3 getcwd)
- getline (man 3 getline)
- getpid (man 2 getpid)
- isatty (man 3 isatty)
- kill (man 2 kill)
- malloc (man 3 malloc)
- open (man 2 open)
- opendir (man 3 opendir)
- perror (man 3 perror)
- printf (man 3 printf)
- fprintf (man 3 fprintf)
- vfprintf (man 3 vfprintf)
- sprintf (man 3 sprintf)
- putchar (man 3 putchar)
- read (man 2 read)
- readdir (man 3 readdir)
- signal (man 2 signal)
- stat (__xstat) (man 2 stat)
- lstat (__lxstat) (man 2 lstat)
- fstat (__fxstat) (man 2 fstat)
- strtok (man 3 strtok)
- wait (man 2 wait)
- waitpid (man 2 waitpid)
- wait3 (man 2 wait3)
- wait4 (man 2 wait4)
- write (man 2 write)


## Project structure
- [shell.h](./shell.h) : Header file.
- [main.c](./main.c)
- [find_command_path.c]
- [shell.c]
- [split_line.c]
- [execute_command.c]




## How to use ?
Here is how to use the shell:

- Compile with `gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh`
- Then execute `./hsh`
- Now in the shell, use it like a normal shell
- Don't forget to write `exit` or tap `CTRL + D` to leave the shell.

## Flowchart
![Flowchart](image/flowchart.png)

## Bugs
Feel free to let us know if you see any bug regarding the code.

## Credits
This project is presented by:
- [Jules Tertre](https://github.com/notsayy)
- [Ephely Koke](https://github.com/ephely)