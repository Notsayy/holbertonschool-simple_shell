# Holberton Simple Shell

This project is meant to create a Simple Shell. It's a basic recreation of a Unix command interpreter that provides a command-line interface for users to interact with the operating system.
## Flowchart
![Flowchart](image/flowchart.png)
## Requirements

### Compilation
The compilation command used is:
`gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh`.

### To Know
- the version of Ubuntu will be Ubuntu 20.04 LTS
- the code have to respect Betty style
- forbid to use mor than 5 functions per file
- all files will have ["shell.h"](./shell.h) as the header file ("#include shell.h")
- global variables are forbidden

### Allowed functions
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
- (Will be updated soon)
- [shell.c](./shell.c): contain the main implementation of our mini Shell.

## Output
The program must have the exact same output as `sh (/bin/sh)` as well as the exact same error output.

The only difference is when an error is printed, the name of the program must be equivalent to our executable file.  
Example of error with `sh`:


julien@ubuntu:/# echo "qwerty" | /bin/sh  
/bin/sh: 1: qwerty: not found  
julien@ubuntu:/# echo "qwerty" | /bin/../bin/sh  
/bin/../bin/sh: 1: qwerty: not found  


Same error with your program `hsh`:

julien@ubuntu:/# echo "qwerty" | ./hsh  
./hsh: 1: qwerty: not found  
julien@ubuntu:/# echo "qwerty" | ./././hsh  
./././hsh: 1: qwerty: not found  

# Simple Shell Project Features

## Basic Functionality
- Display a prompt and wait for user input
- Execute simple commands without arguments
- Handle errors and "end of file" condition (Ctrl+D)

## Command Execution
- Execute commands with arguments
- Handle the PATH to find executables
- Avoid calling fork if the command doesn't exist

## Built-in Commands
- Implement the `exit` built-in command
- Implement the `env` built-in command to print the current environment

## Error Handling
- Display error messages for non-existent executables
- Proper error output matching /bin/sh

## Other Features
- Support for interactive and non-interactive modes
- Minimal memory leaks
- Adherence to Betty coding style

## Bugs
Don't hesitate to let us know if you see any bug regarding the code.

## Credits
This project is presented by:
- [Jules Tertre](https://github.com/notsayy)
- [Ephely Koke](https://github.com/ephely)