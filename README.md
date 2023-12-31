# minishell
In the 42 project, we are redeveloping our own version of a compact bash. It's a program designed to interpret prompts and initiate executables with arguments, incorporating several built-in functionalities.

## How to use it

Using ``make`` will create the ``minishell`` executable.
Simply run it with :

```
make && ./minishell
```

### Available options

Minishell can execute programs using either absolute paths, relative paths, or paths found in the environment (like ``/bin/ls`` or simply ``ls``), and this includes passing arguments or options. Single (``' '``) and double quotes (``" "``) function identically to bash, except they do not support commands spread over multiple lines.

the shell supports using redirections (``>``, ``>>``, ``<``, ``<<``) and pipes (``|``).

It also manages environment variables, such as ``$HOME``, and captures the return status code ``$?``.

Additionally, Minishell responds to ``Ctrl-C`` for interruption, ``Ctrl-\`` for quitting a program, and ``Ctrl-D`` to input an EOF, all in the same manner as bash.

Several functionalities are "built-in", which means they are reimplemented within Minishell rather than invoking external executables. These include commands like ``echo``, ``pwd``, ``cd``, ``env``, ``export``, ``unset``, and ``exit``.

### Version
Apple clang version 11.0.0 (clang-1100.0.33.17)
