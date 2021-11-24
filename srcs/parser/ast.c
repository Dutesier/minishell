/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dareias- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 10:29:40 by dareias-          #+#    #+#             */
/*   Updated: 2021/11/24 15:10:20 by dareias-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ast *init_ast(int type)
{
	//printf("Entered: init_ast\n");
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
	/*int b = 0;
	while (parent->branches && parent->branches[b] != NULL)
	{
		printf("-----Parent %s starts with ->%s<- \n", ast_to_str(parent->e_type), parent->branches[b++]->my_tok->value);
	}*/

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

	/*i = 0;
	while (parent->branches && parent->branches[i] != NULL)
	{
		printf("-----Added ->%s<- to the parents %s branches\n", parent->branches[i++]->my_tok->value, ast_to_str(parent->e_type));
	}*/
	//printf("->Left: ast_add_branch\n");
}

int ast_branch_ammount(t_ast *ast)
{
	int i;

	i = 0;
	while (ast && ast->branches && ast->branches[i] != NULL)
		i++;
	return (i);
}
