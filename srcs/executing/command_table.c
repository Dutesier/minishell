/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_table.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dareias- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 15:58:18 by dareias-          #+#    #+#             */
/*   Updated: 2021/12/06 16:50:12 by dareias-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	command_table(t_shell *shell, t_ast *root)
{
	int count;
	int i;
	//printf("Entered command table \n");

	count = compound_ammount(root, 0);
	i = 0;
	shell->commands = malloc(sizeof(t_comm *) * (count + 1));
	if (!shell->commands)
		return (0);
	while (i < count)
	{
		shell->commands[i] = init_command(shell, root->branches[i]);
		i++;
	}
	shell->commands[i] = NULL;
	//printf("Built %i commands in command table \n", i);
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
