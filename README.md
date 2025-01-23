# MiniShell for Linux

This is a minimal shell implementation for UNIX-like systems. It is a simple
shell that can execute commands, output execution time and display exit status
of the command.

## Internal commands

The shell has a few internal commands that are implemented in the shell itself.
The list will be updated as more commands are added.

- `exit`: Exits the shell.
- `cd`: Changes the current working directory.
- `pwd`: Prints the current working directory.

## External commands

The shell can execute external commands that are available in the system. The
commands are executed using the `execvp` system call. The shell will search for
the command in the directories listed in the `PATH` environment variable.

## Building

If you are willing to try out the shell, you can use the following commands to
build the shell.

```bash
mkdir build
cd build
cmake ..
cmake --build .
```

The built shell will be located in the `./build/apps/shell` directory.

## Installing

You can install the shell using the following command.

```bash
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Release .. --target msh
cmake --build .
sudo cmake --install .
```

The shell will be installed in the `/usr/local/bin` directory. You can run it
using the `msh` command.
