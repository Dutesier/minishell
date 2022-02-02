/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jibanez- <jibanez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 14:51:49 by dareias-          #+#    #+#             */
/*   Updated: 2022/01/31 13:05:48 by jibanez-         ###   ########.fr       */
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

void handle_sigtstp(int sig)
{
	char *prompt;

	prompt = "\033[0;34m$\033[0;37m ";
	if (sig == SIGINT) // Signal handle for ^C
		printf("\n%s", prompt);
	else if (sig == SIGQUIT)
		printf("\n%s", prompt);
}

void init_shell(t_shell *shell, char **envp)
{
	shell->loop = 1;
	shell->envp = envp;
	shell->line = NULL;
	shell->debug = 0;
	shell->vars = NULL;
	shell->exports = NULL;
	shell->prompt = "\033[0;34m$\033[0;37m ";
	shell->sa.sa_handler = &handle_sigtstp;
	shell->sa.sa_flags = SA_RESTART;
	init_termcaps(shell);
	sigaction(SIGINT, &shell->sa, NULL);
	sigaction(SIGQUIT, &shell->sa, NULL);
}

int main(int argc, char *argv[], char **envp)
{
	t_shell shell;
	
	init_shell(&shell, envp);
	if (argc > 1)
		if (ft_strcmp(argv[1], "-debug", ft_min(ft_strlen(argv[1]), 6)))
			shell.debug = 1;
	while (shell.loop)
	{
		canonical_off(&shell);
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
	if (shell.exports)
		clean_exports(&shell);
	clear_history();
	
	return (EXIT_SUCCESS);
}

