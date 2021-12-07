/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dareias- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 15:27:56 by dareias-          #+#    #+#             */
/*   Updated: 2021/12/07 12:22:55 by dareias-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ast_handler(t_shell *shell, t_ast *root)
{
	int i;

	i = 0;
	command_table(shell, root);
	i = run_comm_table(shell);
	/*
	b = root->branches[1];
	if (b->e_type == AST_COMMAND)
	{
		// Check for predefined commands
		if (is_command(root->branches[0]->my_tok->value))
			// reroute this to commands
			i = 1;
		else
			i = init_command(shell, root);
	}*/
	return (i);
}

int branch_ammount(t_ast *ast)
{
	int	i;

	i = 0;
	while (ast->branches && ast->branches[i] != NULL)
		i++;
	return (i);
}
