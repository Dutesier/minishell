/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jibanez- <jibanez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 14:51:49 by dareias-          #+#    #+#             */
/*   Updated: 2022/01/30 00:57:52 by jibanez-         ###   ########.fr       */
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
	{
		printf("Exit: \n");
		kill(0, SIGCHLD);
	}
}

int main(int argc, char *argv[], char **envp)
{
	t_shell shell;
	int i;
	int debug;
	char *prompt;
	
	i = 1;
	debug = 0;
	shell.envp = envp;
	shell.line = NULL;
	shell.debug = &debug;
	shell.vars = NULL;
	shell.exports = NULL;
	shell.sa.sa_handler = &handle_sigtstp;
	shell.sa.sa_flags = SA_RESTART;

	init_termcaps(&shell);
	sigaction(SIGINT, &shell.sa, NULL);
	sigaction(SIGQUIT, &shell.sa, NULL);
	if (argc > 1)
		if (ft_strcmp(argv[1], "-debug", ft_min(ft_strlen(argv[1]), 6)))
			*shell.debug = 1;
	prompt = "\033[0;34m$\033[0;37m ";
	while (i)
	{
		canonical_off(&shell);
		shell.line = get_line(prompt, shell.line);
		if (shell.line != NULL)
		{
			if (shell.line[0] == 'q')
			{
				printf("exit\n");
				i = 0;
			}
			else
			{
				parse_line(&shell);
				clean_shell(&shell);
			}
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

