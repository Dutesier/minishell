/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_shell.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jibanez- <jibanez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 19:42:07 by dareias-          #+#    #+#             */
/*   Updated: 2022/02/15 18:23:33 by jibanez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
*	What mallocs do we have?
*	1 For the command table
*	1 for each command
*	1 for each substr "comm.cmd"
*	1 for shell line
*/

int	clean_shell(t_shell *shell)
{
	int	i;

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
	if (shell->commands)
		free(shell->commands);
	/*if (shell->vars)
		clean_vars(shell);*/
	return (i);
}

int	clean_vars(t_shell *shell)
{
	int	i;

	i = 0;
	while (shell->vars && shell->vars[i] != NULL)
	{
		free(shell->vars[i]);
		i++;
	}
	if (shell->vars)
		free(shell->vars);
	return (i);
}

int	clean_exports(t_shell *shell)
{
	int	i;

	i = 0;
	while (shell->exports && shell->exports[i])
	{
		free(shell->exports[i++]);
	}
	free(shell->exports);
	return (i);
}

int clean_envp(t_shell *shell)
{
	int i;

	i = 0;
	while (shell->envp && shell->envp[i])
		free(shell->envp[i++]);
	if (shell->envp)
		free(shell->envp);
	return (i);
}
