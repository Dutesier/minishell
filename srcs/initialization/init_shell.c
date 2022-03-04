#include "minishell.h"

void	handle_sig(int sig)
{
	// char	*prompt;

	if (sig == SIGINT)
	{
	    printf("\n"); // Move to a new line
    	rl_on_new_line(); // Regenerate the prompt on a newline
    	rl_replace_line("", 0); // Clear the previous text
    	rl_redisplay();
    }
}

void	init_shell(t_shell *shell, char **envp)
{
	shell->loop = 0;
	shell->last_exit = 0;
	shell->envp = dup_envp(envp);
	shell->line = 0;
	shell->debug = 0;
	shell->vars = NULL;
	shell->exports = NULL; // We can probably delete this
	shell->prompt = NULL;
	shell->sa.sa_handler = &handle_sig;
	shell->sa.sa_flags = SA_RESTART;

    shell->io.save_in = -1;
	shell->io.save_out = -1;
	shell->io.saved_in = 0;
	shell->io.saved_out = 0;
    shell->io.current_in = STDIN_FILENO;
    shell->io.current_out = STDOUT_FILENO;
	shell->io.my_pipe[0] = -1;
	shell->io.my_pipe[1] = -1;
	init_termcaps(shell);
}