/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_table.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dareias- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 15:58:18 by dareias-          #+#    #+#             */
/*   Updated: 2021/12/06 19:37:43 by dareias-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int comm_table_pipes(t_shell *shell, t_ast *root);

int	command_table(t_shell *shell, t_ast *root)
{
	int count;
	int i;
	int x;
	//printf("Entered command table \n");

	count = compound_ammount(root, 0);
	i = 0;
	x = 0;
	shell->commands = malloc(sizeof(t_comm *) * (count + 1));
	if (!shell->commands)
		return (0);
	while (i < count)
	{
		if (root->branches[i + x]->e_type == AST_WORD)
			x++;
		shell->commands[i] = init_command(shell, root->branches[i + x]);
		i++;
	}
	shell->commands[i] = NULL;
	comm_table_pipes(shell, root);
	//printf("Built %i commands in command table \n", i);
	return (i);
}

static void set_as_piper(t_shell *shell, int i, int fd[])
{
	if (shell->commands[i]->piping == 0)
		shell->commands[i]->piping = 2;
	else
		shell->commands[i]->piping = 3;
	shell->commands[i]->fd_n[0] = fd[0];
	shell->commands[i]->fd_n[1] = fd[1];
}

static void set_as_piped(t_shell *shell, int i, int fd[])
{
	if (shell->commands[i]->piping == 0)
		shell->commands[i]->piping = 1;
	else
		shell->commands[i]->piping = 3;
	shell->commands[i]->fd_p[0] = fd[0];
	shell->commands[i]->fd_p[1] = fd[1];
}

static int comm_table_pipes(t_shell *shell, t_ast *root)
{
	int i;
	int x;
	int fd[2];

	i = 0;
	x = 0;
	while (root->branches && root->branches[x])
	{
		if (root->branches[x]->e_type == AST_WORD)
		{
			if (pipe(fd) < 0)
				return (0);
			if (x > 0)
				set_as_piper(shell, i - 1, fd);
			if (shell->commands[i] != NULL)
				set_as_piped(shell, i, fd);
			x++;
		}
		i++;
		x++;
	}
	return (i);
}

int run_comm_table(t_shell *shell)
{
	int i;

	i = 0;
	while (shell->commands && shell->commands[i] != NULL)
	{
		comm_printer(shell->commands[i]);
		if (shell->commands[i]->e_type == VAR_DEF)
		{
			// FIXME: Need to build a fucntion that sets and stores a variable
			i++;
		}
		else
		{
			run_command(shell->commands[i++]);
		}
	}
	return (i);
}
