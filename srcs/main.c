/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jibanez- <jibanez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 14:51:49 by dareias-          #+#    #+#             */
/*   Updated: 2022/02/28 20:29:33 by jibanez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * Four main steps:
 * 1 - Initialize the program
 * 2 - Read and parse the command given
 * 3 - Execute given command
 * 4 - Clean and exit
 *
 * Steps 2 & 3 run on a loop
 *
*/

void	handle_sig(int sig)
{
	char	*prompt;

	prompt = "\033[0;34m$\033[0;37m ";
	
	if (sig == SIGINT)
	{
	    printf("\n"); // Move to a new line
    	rl_on_new_line(); // Regenerate the prompt on a newline
    	rl_replace_line("", 0); // Clear the previous text
    	rl_redisplay();
	}
	else if (sig == SIGKILL)
	{
		ft_putstr_fd("ctrl + D\n", 1);
		ft_putstr_fd("\rQuit\n", 1);

	}
	// write(1, "Went through here\n", 19);
	// printf("%d %s", sig, prompt);
}

void	init_shell(t_shell *shell, char **envp)
{
	shell->loop = 0;
	shell->last_exit = 0;
	shell->envp = dup_envp(envp);
	shell->line = 0;
	shell->debug = 0;
	shell->vars = NULL;
	shell->exports = NULL;
	shell->prompt = NULL;
	shell->sa.sa_handler = &handle_sig;
	shell->sa.sa_flags = SA_RESTART;
	shell->save_in = -1;
	shell->save_out = -1;
	shell->saved = 0;
	init_termcaps(shell);
}

int	main(int argc, char *argv[], char **envp)
{
	t_shell	shell;

	init_shell(&shell, envp);
	
	// FOR TESTING ONLY
	// argv[2] will contains the content of the line for example "echo something ; ls -la"
	if (argc >= 3 && !ft_strcmp(argv[1], "-c", 3))
	{
		int exit_status = interactive_mode(&shell, argv);
		exit(exit_status);
	}
    // Above this is the function that normally launch your minishell, instead
    // of reading line with a get_next_line or a read() on fd 0, you just have to get
    // the argv[2] (which contains the content) and execute it.
    // Your function should return the good exit status otherwise the tests may be considered as false.

	if (argc > 1 && ft_strcmp(argv[1], "-debug", ft_min(ft_strlen(argv[1]), 6)))
		shell.debug = 1;
	else if (argc > 1)
		return (interactive_mode(&shell, argv));
	shell.loop = 1;
	while (shell.loop)
	{
		canonical_off(&shell);
		signal(SIGINT, handle_sig);
		signal(SIGQUIT, SIG_IGN);
		get_line(&shell);
		if (shell.line != NULL)
		{
			parse_line(&shell);
			clean_shell(&shell);
		}
		canonical_on(&shell);
	}
	if (shell.vars)
		clean_vars(&shell);
	/*if (shell.exports)
		clean_exports(&shell);*/
	if (shell.envp)
		clean_envp(&shell);
	clear_history();
	return (EXIT_SUCCESS);
}
