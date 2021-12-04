# minishell
## Build a simplified version of a shell
### Your shell should:
- [ ] Not interpret unclosed quotes or unspecified special characters like \ or ;.
- [ ] Not use more than one global variable, think about it and be ready to explain why
you do it.
- [x] Show a prompt when waiting for a new command.
- [x] Have a working History.
- [ ] Search and launch the right executable (based on the PATH variable or by using
relative or absolute path)
- It must implement the builtins:
 - [ ]   echo with option -n
 - [ ]   cd with only a relative or absolute path
 - [ ]   pwd with no options
 - [ ]   export with no options
 - [ ]   unset with no options
 - [ ]   env with no options or arguments
 - [ ]   exit with no options
 - [ ]   ’ inhibit all interpretation of a sequence of characters.
 - [ ]   " inhibit all interpretation of a sequence of characters except for $.
- Redirections:
 - [ ]   "<" should redirect input.
 - [ ]   ">" should redirect output.
 - [ ]   “<<” read input from the current source until a line containing only the delimiter is seen. it doesn’t need to update history!
 - [ ]   “>>” should redirect output with append mode.
 - Pipes 
   - [ ]  "|". The output of each command in the pipeline is connected via a pipe to the
	  input of the next command.
 - [ ]   Environment variables ($ followed by characters) should expand to their values.
 - [ ]   $? should expand to the exit status of the most recently executed foreground
	  pipeline.
 - [ ]   ctrl-C ctrl-D ctrl-\ should work like in bash.
- When interactive:
  - [ ]   ctrl-C print a new prompt on a newline.
  - [ ]   ctrl-D exit the shell.
  - [ ]   ctrl-\ do nothing.
 
readline function can produce some leaks, no need to fix this.

For every point, if you have any doubt take bash as a reference.

### File Organization
| Folder      | Description |
| ----------- | ----------- |
| Parser     | Contains a parser and a lexer that build an Abstract Syntax Tree. The goal is to read the input provided from the user and separate it into actionable commands. Also checks for syntax errors.      |
| Cleaning   | Contains functions to make sure that we go into the next phase (i.e. exiting or new line from user) cleanly. Frees any unnecessary memory. |
| Commands   | Contains functions to replicate bash commands that need to be hardcoded. "cd" is a good example, since we cannot fork and then call chdir because when we exit the fork we'll be left in the same directory. |
| Executing   | Executes commands given by the parser via ```execve```. |
| Redirecting | Takes care of redirecting STDIN and STDOUT when necessary. A good example is that it creates the pipes needed between two processes when givne the ```pipe``` command. |
| Reader | Uses the ```readline``` functions to read a line from the user and create a working history. |
| Utils | Helpful everyday functions. |

### External functions that are allowed
- readline, rl_clear_history, rl_on_new_line, rl_replace_line, rl_redisplay, add_history,
- printf, malloc, free, write,
- access, open, read, close,
- fork, wait, waitpid, wait3, wait4,
- signal, sigaction, kill,
- exit,
- getcwd,
- chdir,
- stat, lstat, fstat,
- unlink,
- execve, dup, dup2, pipe,
- opendir, readdir, closedir,
- strerror, perror,
- isatty, ttyname, ttyslot,
- ioctl, getenv, tcsetattr, tcgetattr, tgetent, tgetflag, tgetnum, tgetstr, tgoto, tputs.
