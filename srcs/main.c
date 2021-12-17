/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dareias- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 14:51:49 by dareias-          #+#    #+#             */
/*   Updated: 2021/12/17 18:03:40 by dareias-         ###   ########.fr       */
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
	if (argc > 1)
		if (ft_strcmp(argv[1], "-debug", ft_max(ft_strlen(argv[1]), 6)))
			*shell.debug = 1;
	prompt = "\033[0;34m$\033[0;37m ";
	while (i)
	{
		shell.line = get_line(prompt, shell.line);
		if (shell.line != NULL)
		{
			if (shell.line[0] != 'q')
			{
				parse_line(&shell);
				clean_shell(&shell);
			}
			else
				i = 0;
		}
	}
	clear_history();
	
	return (0);
}

