/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_command_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dareias- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 12:25:55 by dareias-          #+#    #+#             */
/*   Updated: 2021/12/16 15:54:07 by dareias-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int init_comm_redir(t_comm *comm, t_ast *ast, int r)
{
	int i;
	t_ast *b;

	i = 0;
	b = ast->branches[r];
	while (b->branches[i] != NULL)
	{
		if (b->branches[i]->my_tok->e_type == TOK_SPACE) 
			i++;
		if (b->branches[i]->my_tok->e_type == TOK_GT)
			comm->redir = 1;
		else if (b->branches[i]->my_tok->e_type == TOK_LT)
			comm->redir = 2;
		else if (b->branches[i]->my_tok->e_type == TOK_ARROW_RIGHT)
			comm->redir = 3;
		else if (b->branches[i]->my_tok->e_type == TOK_ARROW_LEFT)
			comm->redir = 4;
		i++;
	}
	return (config_redir(comm, b, comm->redir));
}

int config_redir(t_comm *comm, t_ast *ast, int redir)
{
	int i;

	i = 0;
	while (ast->branches[i] && ast->branches[i]->my_tok->e_type != TOK_WORD)
		i++;
	if (!ast->branches[i])
		return (0);
	if (redir == 1 || redir == 3)
	{
		comm->outfile = ft_strdup(ast->branches[i]->my_tok->value);
	}
	if (redir == 2)
	{
		comm->infile = ft_strdup(ast->branches[i]->my_tok->value);
	}
	if (redir == 4)
	{
		comm->heredoc = ft_strdup(ast->branches[i]->my_tok->value);
	}

	printf("Redir %i i %i\n", redir, i);
	return (redir);
}

int find_redir_branch(t_ast *ast)
{
	int i;
	int count;
	int nor;

	i = 0;
	count = 0;
	nor = -1;
	while (ast->branches[i] != NULL)
	{
		if (ast->branches[i]->e_type == AST_REDIRECT)
		{
			count = i + count * 10;
			nor = 1;
		}
		i++;
	}
	if (nor == -1)
		return (-1);
	return (count);
}

int find_cmd_branch(t_ast *ast)
{
	int i;

	i = 0;
	while (ast->branches[i] != NULL && ast->branches[i]->e_type != AST_COMMAND)
		i++;
	return (i);
}

int find_args_branch(t_ast *ast)
{
	int i;
	int noa;

	i = 0;
	noa = -1;
	while (ast->branches[i] != NULL)
	{
		if (ast->branches[i]->e_type == AST_COMM_ARGS)
		{
			noa = 1;
			break ;
		}
		i++;
	}
	if (noa == -1)
		return (noa);
	return (i);
}
