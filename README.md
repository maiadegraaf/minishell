# minishell

<p align="center">
  <a href="https://github.com/maiadegraaf">
    <picture>
    <img alt="philosophers" src="https://user-images.githubusercontent.com/68693691/193606493-2969e425-6bad-44ce-97af-89fec62bee22.gif" width=500>
    </picture>
  </a>
</p>

*A mini recreation of bash.  Implementing previously learned concepts like file descriptors and processes.  Made with [Alfred Polycarpe](https://github.com/Alfredpoly).*

## The Challenge
This was probably the biggest project I've done so far, as well as the first one I did as a group.  The goal was to create a mini version of bash, I say mini but it was still a huge project.  We had to learn how bash takes arguments, parses them, and executes them. We had to incorporate the following features:
- Display a promt while waiting for a new commmand.
- Have a working history.
- Find and launch executables (using the `PATH` variable or an absolute path).
- Handle `'` (single) and `"` (double) **quotes** like in bash.
- Implement **redirections** such as:
  - `<` redirect input.
  - `>` redirect output.
  - `<<` heredoc (doesn't affect history).
  - `>>` redirect output in append mode.
- Implement `|` (**pipes**).
- Handle **environment variables**.
- Handle `$?`.
- `ctrl-C`, `ctrl-D`, and `ctrl-\` should behave like in bash.
- Recreate the following **builtins**:
  - `echo` with option `-n`.
  - `cd` with only a relative or absolute path.
  - `pwd` (no flags).
  - `export` (no flags).
  - `unset` (no flags).
  - `env` (no flags or arguments).
  - `exit` (no flags).

We didn't have to implement && and ||, or wildcards, as well as any special symbols that weren't specifically asked for.  We were also told that when in doubt, take bash as a reference.  This sometimes led to discussions on wether or not we had to implement something, the result of which was usually "probably??? 🤷‍♀️".

### What Is Bash and How Does It Work?
The shell is a program that the user can use to interact with an operating system's services. Bash is the GNU shell, and is currently the most common shell program.  We took the challenge of recreating bash very literally, so the first thing we did was learn how bash actually works with the help of [this article](https://www.cs.purdue.edu/homes/grr/SystemsProgrammingBook/Book/Chapter5-WritingYourOwnShell.pdf).  Essentially it breaks down the process into 4 steps: `lexer` → `parser` → `expander` → `executor`, which we replicated in our project.

## Implementation
### The Lexer


## Installation
### Clone the repository:
``` 
git clone https://github.com/maiadegraaf/minishell.git
cd minishell
make
```

### Some commands to try: