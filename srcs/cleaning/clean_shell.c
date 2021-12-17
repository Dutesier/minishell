/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_shell.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dareias- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 19:42:07 by dareias-          #+#    #+#             */
/*   Updated: 2021/12/17 18:39:50 by dareias-         ###   ########.fr       */
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
	if (shell->vars)
		clean_vars(shell);
	free(shell->commands);
	//free(shell->line);
	return (i);
}

int clean_vars(t_shell *shell)
{
	//printf("cleaning vars\n");
	int i;

	i = 0;
	while (shell->vars && shell->vars[i] != NULL)
	{
		free(shell->vars[i]);
		i++;
	}
	free(shell->vars);
	return (i);
}
