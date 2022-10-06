# minishell

<p align="center">
  <a href="https://github.com/maiadegraaf">
    <picture>
    <img alt="philosophers" src="https://user-images.githubusercontent.com/68693691/193606493-2969e425-6bad-44ce-97af-89fec62bee22.gif" width=500>
    </picture>
  </a>
</p>

*A mini recreation of bash.  Implementing previously learned concepts like file descriptors and processes.  Made with [Alfred Polycarpe](https://github.com/Alfredpoly).*

## Table of Contents
- [The Challenge](#the-challenge)
  - [What Is Bash and How Does It Work?](#what-is-bash-and-how-does-it-work)
- [Implementation](#implementation)
  - [The Lexer](#the-lexer)
  - [The Parser](#the-parser)
  - [Builtins](#builtins)
  - [Executor](#executor)
    - [Expander](#expander)
    - [Heredoc](#heredoc)
    - [Single Command](#single-command)
    - [Multiple Commands](#multiple-commands)
  - [Reset](#reset)
- [My Take Away](#my-take-away)
- [Installation](#installation)

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
	char    	*str;
	t_tokens        token;
	int		i;
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
	char                    **str;
	int                     (*builtin)(t_tools *, struct s_simple_cmds *);
	int                     num_redirections;
	char                    *hd_file_name;
	t_lexer                 *redirections;
	struct s_simple_cmds	*next;
	struct s_simple_cmds	*prev;
}	t_simple_cmds;
```

The first thing the parser does is loop through the lexer list until it encounters a pipe.  It then takes all the nodes before the pipe as one command, and creates a node in the `t_simple_cmds` struct.  If it doesn't find a pipe it takes all the (remaining) nodes as one command.

![parser 001](https://user-images.githubusercontent.com/68693691/194295673-3c9e17c3-d5ab-40dc-82ef-72b909f4acb3.png)
*The parser takes the `t_lexer` list (left) and converts it into the `t_simple_cmds` list (right)*

For each command it first checks for redirections, which it stores in the `*redirections` linked list, which holds both the token and the filename or delimiter in the case of a heredoc.  When the nodes are added to the `*redirections` list, they are deleted from the lexer list.  Next it checks if the first word is a builtin, in which case it stores a function pointer to the corresponding function, more on this bellow. As the redirections have been removed from the lexer list, the parser can easily combines all remaining words into a 2D array, which is a required execve argument.  It also makes it easier to handle situations where the words may be seperated by redirections, for example:
```
cat > file -e
```
As `>` and `file` are already deleted from the lexer list when they are added to the redirections list, all that remains is `cat` and `-e`.  Which then can easily be added into an array.

This process is repeated until the end of the lexer list.

### Builtins
We handle builtins, as discussed above through storing a function pointer in the `t_simple_cmds`.  We achieve this by sending the the first word of a command to a function `builtin_arr` which loops through a static array of the different builtin functions.  If it finds a corresponding function it returns it to the parser, else it returns `NULL`.  For me, this was a way to learn about function pointers, which I had never worked with before. Also by determining the builtin at the parser stage, it greatly simplifies the executor as executing the builtin requires just two lines of code:
``` C
if (cmd->builtin != NULL)
  cmd->builtin(tools, cmd);
```
The builtins we incorporated (as per the subject) are:
| Command | Description |
|---|---|
|`cd`| Changes the working directory of the current shell execution environment and updates the environment variables `PWD` and `OLDPWD`. <br>Without arguments it change the working directory to the home directory.  <br>`-` changes the directory to the `OLDPWD`. |
|`echo`| Displays a line of text<br>Optional flag `-n`: do not output the trailing newline|
|`env` | Displays the environment variables|
|`exit`| Terminates the shell.<br>Accepts optional argument `n`, which sets the exit status to `n`. |
|`export`| Accepts arguments `name[=value]`.<br>Adds name to the environment.  Set's value of name to `value`.<br>If no argument is given, displays list of exported variables.|
|`pwd`| Shows the current directory as an absolute path.|
|`unset`|Accepts argument `name`. <br> Removes the variable `name` from the environment.|

### Executor
When the parser returns the `t_simple_cmds` list back to `minishell_loop`, a simple check is done to determine how many commands there are, as they are handled by different functions.  However, with the exception of a few builtins, the commands are ultimately executed by the same function `handle_cmd`, which finds, and if successful, executes the command.

#### Expander
Before a node from `t_simple_cmds` is handled it is expanded.  The expander takes variables, identified by `$`, and replaces them with their value from the environment variables.  Such that `$USER` becomes `mgraaf`, and `$?` is replaced with the exit code.

#### Heredoc
Before creating a child process, the parent process executes heredocs.  We handled heredocs by creating a temporary file to write the input to.  The filename is stored in the related `t_simple_cmds` node so that it can be used to replace `STDIN`.  If there are multiple heredocs in a single `t_simple_cmds` node, then the file name ultimately stored would be that of the last heredoc. Using a file comes with limitations and security issues however we felt it was the simplest way dealing with it, and is close to how bash does it.

#### Single Command
Like in bash, builtin commands, specifically `cd`, `exit`, `export`, and `unset` cannot be run in a separate process, as then the environmentally variable cannot be properly altered.  If there is only one command, and it is one of the aforementioned builtins, it is executed in the parent process and the function returns back to the `minishell_loop`. If the command is not a builtin the single command function creates a new process and sends the command to `handle_cmd`.

#### Multiple Commands
If there are multiple commands, the executor loops through each `t_simple_cmds` node and creates a child process for it using `fork()`, and  using `pipe()` creates a pipe in order to send the output of one command as the input to the next.  Checkout [pipex](https://github.com/maiadegraaf/pipex) to learn more about these functions.

Essentially for each command the following happens:
1. The command is expanded.
2. A pipe is created with `end[0]` and `end[1]`, except the last command.
3. Using `fork()` a child process is created. In the child process:
   1. With the exception of the first command, `dup2` replaces `STDIN` with the output of the previous command.
   2. With the exception of the last command, `dup2` replaces `STDOUT` with `end[1]`.
   3. In the case of redirections, the `STDIN` or `STDOUT` is replaced with their respective file descriptors. 
   4. `handle_cmd` finds and executes the command.
4. `end[0]` is stored for the next command.

The parent process then waits for all the children to end, then returns back to the `minishell_loop`.

### Reset
The program then does a full reset, freeing all nodes that have not been freed or deleted yet, and resets various variables so that the program can start again by displaying a new prompt.

## My Take Away
As previously mentioned, this was the first project I did in a group, which for me was an overall joyful experience.  This is a huge and daunting project and doing it alone would have been a massive challenge.  What I think we did well was dividing up the different parts of the project while also supporting each other if we ran into issues.  Although I wrote most of the lexer and parser, Alfred did contribute to both.  I also wrote the executor while Alfred worked on the builtins and expander.

By far the hardest part of this project was handling all the edge cases.  Before handing in the project we had done our best to manage all of the ones we we're aware of, which was a considerable list.  Often by solving one case, we would break another part of our code.  The easiest way to handle an edge case was by replicating and understanding the way bash does it.  However in some cases it was a complete mystery which only made it more confusing.  Only once we handed in the project the first time did we discover how many edge cases there truly were as each person who evaluated us found new holes in our program.  In the end we passed the second time we handed it in, after correcting all the issues.

## Installation
### Clone the repository:
``` 
git clone https://github.com/maiadegraaf/minishell.git
cd minishell
make
```
### Run Minishell
```
./minishell
```

### Some commands to try:

As this project is made to mimic bash, you can try any commands you normally would try in bash.

If you really can't think of anything try some of the following.  You do have to enter each line separately as the program doesn't handle new lines.
```
ls -la | grep a | tr 'a-z' 'A-Z'
```

```
cat << EOF > file
cat file
rm file
```

```
ls | rev > file
cat file
rev file | cat
rm file
```

*to exit the program:*
```
exit
```