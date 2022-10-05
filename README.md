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

![bash steps](https://user-images.githubusercontent.com/68693691/193665518-0c0c7fec-38a9-4f6c-91ca-fef606abfb0d.png)


I'll delve further into each step in the implementation section bellow.

## Implementation

The program is run without arguments (and will throw an error if any are used).  The program essentially comprises of two functions that call each other indefinitely.  The first, `minishell_loop` performs the functions of minishell, the other cleans up and prepares for the next line.  In `minishell_loop`, a command prompt shows up, which is implemented through [readline](https://www.man7.org/linux/man-pages/man3/readline.3.html).  This also allowed us to use the built-in history function.  Once a line has been inputted it checks for any unclosed quotes.  If it doesn't find any it sends the line to the lexer.

### The Lexer
The lexer, also called the tokenizer, takes as the entered line as input. It then reads through the line word by word, using white space as delimiters.  First it checks wether or not the word is a token, ie: `|`, `<`, `<<`, `>`, or `>>`, and otherwise it assumes it is a word.  Which it then adds to the following linked list:

```C
typedef struct s_lexer
{
	char			*str;
	t_tokens		token;
	int				i;
	struct s_lexer	*next;
	struct s_lexer	*prev;
}	t_lexer;
```
Each node contains either a `char *` containing the word or a `t_token`.  We also assign each node an index so that we can easily delete them later.

### The Parser
The lexer then gets sent to the parser which then groups the different nodes together based on the tokens.  Each group becomes a command.

```C
typedef struct s_simple_cmds
{
	char					**str;
	int					(*builtin)(t_tools *, struct s_simple_cmds *);
	int					num_redirections;
	char					*hd_file_name;
	t_lexer					*redirections;
	struct s_simple_cmds	*next;
	struct s_simple_cmds	*prev;
}	t_simple_cmds;
```

The first thing the parser does is loop through the lexer list until it encounters a pipe.  It then takes all the nodes before the pipe as one command.  Then it checks for redirections, which it stores in the `*redirections` linked list, which holds both the token and the filename or delimiter in the case of a heredoc.  When the nodes are added to the `*redirections` list, they are deleted from the lexer list.  Next it checks if the first word is a builtin, in which case it stores a pointer to the corresponding function. The parser then combines all remaining words into a 2D array, to be passed to execve or the builtin later on.  

### Executor
When the parser returns the simple_cmds table back to `minishell_loop`, a simple check is done to determine how many commands there are, as they are handled by different functions.  However, with the exception of a few builtins, the commands are ultimately executed by the same function.

#### Single Command
Like in bash, builtin commands, specifically `cd`, `exit`, `export`, and `unset` cannot be run in a separate process, as then the environmentally variable cannot be properly altered.  If there is only one command, and it is one of the aforementioned builtins, it is executed in the parent process and the function returns back to the `minishell_loop`. If the command is not a builtin the single command function does create a new process in order to successfully execute it using execve.

#### Multiple Commands
If there are multiple commands, 

## Installation
### Clone the repository:
``` 
git clone https://github.com/maiadegraaf/minishell.git
cd minishell
make
```

### Some commands to try:
