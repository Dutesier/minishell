/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dareias- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 10:29:40 by dareias-          #+#    #+#             */
/*   Updated: 2022/01/21 16:33:16 by dareias-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ast *init_ast(int type)
{
	t_ast *ast;

	ast = malloc(sizeof(t_ast));
	if (!ast)
		return (NULL);
	ast->e_type = type;
	ast->branches = malloc(sizeof(t_ast *));
	if (!ast->branches)
		return (NULL);		
	ast_add_branch(ast, NULL, 0);
	ast->my_tok = NULL;
	return (ast);
}

void ast_add_branch(t_ast *parent, t_ast *child, int i)
{

	int x;
	t_ast **tree;

	tree = malloc(sizeof(t_ast *) * (i + 2));
	if (!tree)
		return ;
	x = 0;
	while (x < i)
	{
		tree[x] = parent->branches[x];
		x++;
	}
	tree[x++] = child;
	tree[x] = NULL;
	if (parent->branches)
		free(parent->branches);
	parent->branches = tree;
}

void ast_add_branch_idx(t_ast *parent, t_ast *child, int i, int idx)
{
	int x;
	int y;
	t_ast **tree;

	if (idx > i)
		return ;
	tree = malloc(sizeof(t_ast *) * (i + 2));
	if (!tree)
		return ;
	x = 0;
	y = 0;
	while (x <= i)
	{
		if (x == idx)
			tree[x++] = child;
		else
		{
			tree[x] = parent->branches[y];
			x++;
			y++;
		}
	}
	tree[x] = NULL;
	if (parent->branches)
		free(parent->branches);
	parent->branches = tree;
}

int ast_branch_ammount(t_ast *ast)
{
	int i;

	i = 0;
	while (ast && ast->branches && ast->branches[i] != NULL)
		i++;
	return (i);
}
