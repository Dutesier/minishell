/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_command_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dareias- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 12:25:55 by dareias-          #+#    #+#             */
/*   Updated: 2021/12/16 19:18:53 by dareias-         ###   ########.fr       */
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
		if (b->branches[i] == NULL)
			break ;

		if (b->branches[i]->my_tok->e_type == TOK_GT)
		{
			comm->redir.writes = 1;
			comm->redir.ammount++;
			config_redir(comm, b, comm->redir.writes);
		}
		else if (b->branches[i]->my_tok->e_type == TOK_LT)
		{
			comm->redir.reads = 2;
			comm->redir.ammount++;
			config_redir(comm, b, comm->redir.reads);
		}
		else if (b->branches[i]->my_tok->e_type == TOK_ARROW_RIGHT)
		{
			comm->redir.appends = 3;
			comm->redir.ammount++;
			config_redir(comm, b, comm->redir.appends);
		}
		else if (b->branches[i]->my_tok->e_type == TOK_ARROW_LEFT)
		{
			comm->redir.heredoc = 4;
			comm->redir.ammount++;
			config_redir(comm, b, comm->redir.heredoc);
		}
		i++;
	}
	return (comm->redir.ammount);
}

int config_redir(t_comm *comm, t_ast *ast, int redir)
{
	int i;

	i = 0;
	while (ast->branches[i] && ast->branches[i]->my_tok->e_type != TOK_WORD)
		i++;
	if (!ast->branches[i])
	{
		comm->redir.ammount = -1;
		return (comm->redir.ammount);
	}
	if (redir == 1 || redir == 3)
	{
		if (comm->outfile)
			free (comm->outfile);
		comm->outfile = ft_strdup(ast->branches[i]->my_tok->value);
	}
	else if (redir == 2)
	{
		if (comm->infile)
			free(comm->infile);
		comm->infile = ft_strdup(ast->branches[i]->my_tok->value);
	}
	else if (redir == 4) // lest handle heredoc here
	{
		if (comm->heredoc_word)
			free(comm->heredoc_word);
		comm->heredoc_word = ft_strdup(ast->branches[i]->my_tok->value);
		if (comm->heredoc_filename)
			free(comm->heredoc_filename);
		comm->heredoc_filename = ft_heredoc(comm);
	}
	return (1);
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
	int count;
	int noa;

	i = 0;
	count = 0;
	noa = -1;
	while (ast->branches[i] != NULL)
	{
		if (ast->branches[i]->e_type == AST_COMM_ARGS)
		{
			count = i + count * 10;
			noa = 1;
		}
		i++;
	}
	if (noa == -1)
		return (noa);
	return (count);
}
