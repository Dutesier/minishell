/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dareias- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 15:27:56 by dareias-          #+#    #+#             */
/*   Updated: 2021/11/24 18:28:01 by dareias-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ast_handler(t_shell *shell, t_ast *root)
{
	int i;
	t_ast *b;

	i = 0;
	b = root->branches[1];
	if (b->e_type == AST_COMMAND)
	{/*
		// Check for predefined commands
		if (is_command(root->branches[0]->my_tok->value))
			// reroute this to commands
			i = 1;
		else*/
			i = init_command(shell, root);
	}
	return (i);
}
