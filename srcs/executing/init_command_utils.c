/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_command_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dareias- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 12:25:55 by dareias-          #+#    #+#             */
/*   Updated: 2021/12/07 12:54:25 by dareias-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int init_comm_redir(t_comm *comm, t_ast *ast)
{
	int i;
	int redir;
	t_ast *b;

	i = 0;
	redir = 0;
	if (branch_ammount(ast) != 3)
		return (0);
	b = ast->branches[2];
	if (b->branches[i]->my_tok->e_type == TOK_SPACE) 
		i++;
	if (b->branches[i]->my_tok->e_type == TOK_GT)
		redir = 1;
	else if (b->branches[i]->my_tok->e_type == TOK_LT)
		redir = 2;
	else if (b->branches[i]->my_tok->e_type == TOK_ARROW_RIGHT)
		redir = 3;
	else
		redir = 4;
	return (config_redir(comm, b, redir));
}

int config_redir(t_comm *comm, t_ast *ast, int redir)
{
	int i;

	i = 0;
	while (ast->branches[i] && ast->branches[i]->my_tok->e_type != TOK_WORD)
		i++;
	if (!ast->branches[i])
		return (0);
	if (redir == 1)
	{
		comm->outfile = ft_strdup(ast->branches[i]->my_tok->value);
	}
	if (redir == 2)
	{
		comm->infile = ft_strdup(ast->branches[i]->my_tok->value);
	}
	return (redir);
}
