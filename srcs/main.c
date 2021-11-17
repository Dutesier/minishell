/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dareias- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 14:51:49 by dareias-          #+#    #+#             */
/*   Updated: 2021/11/17 18:15:10 by dareias-         ###   ########.fr       */
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

	(void)envp;
	(void)argv;
	char *line;
	int i;
	
	i = 1;
	while (i)
	{
		ft_putstr_fd("$ ", 1);
		line = get_next_line(0);
		// Then a function that uses line
		if (line != NULL)
		{
			if (line[0] == 'c')
				ft_cd("..");
			if (line[0] == 'C')
				ft_cd("minishell");
			if (line[0] == 'p')
				ft_pwd();
			if (line[0] == 'q')
				i = 0;
		}
	}

	return (0);
}
