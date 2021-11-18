/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dareias- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 14:51:49 by dareias-          #+#    #+#             */
/*   Updated: 2021/11/17 18:37:14 by dareias-         ###   ########.fr       */
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
	if (argc == 2)
		return (1);

	(void)argv;
	t_shell shell;
	int i;
	
	i = 1;
	shell.envp = envp;
	while (i)
	{
		ft_putstr_fd("$ ", 1);
		shell.line = get_next_line(0);
		// Then a function that uses line
		if (shell.line != NULL)
		{
			//parse_line(&shell);


			if (shell.line[0] == 'q')
				i = 0;
		}
	}

	return (0);
}
