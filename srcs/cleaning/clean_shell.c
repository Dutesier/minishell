/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_shell.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dareias- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 19:42:07 by dareias-          #+#    #+#             */
/*   Updated: 2021/12/22 10:06:04 by dareias-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int clean_shell(t_shell *shell)
{
	// What mallocs do we have?
	// 1 For the command table
	// 1 for each command
	// 1 for each substr "comm.cmd"
	// 1 for shell line
	
	int i;
//	printf("Cleaning Shell \n");

	i = 0;
	while (shell->commands && shell->commands[i] != NULL)
	{
		if (shell->commands[i]->cmd)
			free(shell->commands[i]->cmd);
		if (shell->commands[i]->infile)
			free(shell->commands[i]->infile);
		if (shell->commands[i]->outfile)
			free(shell->commands[i]->outfile);
		if (shell->commands[i]->heredoc)
			free(shell->commands[i]->heredoc);
		free(shell->commands[i]);
		i++;
	}
	free(shell->commands);
//	printf("Cleaned Shell \n");
	//free(shell->line);
	return (i);
}

int clean_vars(t_shell *shell)
{
//	printf("Cleaning vars\n");
	int i;

	i = 0;
	while (shell->vars && shell->vars[i] != NULL)
	{
	//	printf("VAR[%i] (%p) cleaning: %s\n",i, &shell->vars[i],  shell->vars[i]);
		free(shell->vars[i]);
		i++;
	}
	free(shell->vars);
//	printf("Cleaned vars\n");
	return (i);
}
