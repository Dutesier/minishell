/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable_expansion.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dareias- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 15:36:06 by dareias-          #+#    #+#             */
/*   Updated: 2022/02/04 20:12:43 by dareias-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *var_expand(t_ast *ast)
{
	int i;

	i = 0;
	while (ast->branches[i] != NULL)
	{
		if (ast->branches[i]->my_tok->e_type == TOK_WORD)
			return (ast->branches[i]->my_tok->value);
		i++;
	}
	return (NULL);
}

void replace_variables(t_shell *shell, t_ast *ast, t_ast *father)
{
	/*
	We need father so that we can turn the following structure:
	-COMMAND
	--COMM_ARGS <- FATHER
	---VAR_EXP <- AST
	----DOLLAR
	----WORD
	into:
	-COMMAND
	--COMM_ARGS <- FATHER
	---WORD <- Expanded variable
	*/

	//print_ast(father, 0);
	//print_ast(ast, 0);
	int i;
	int c;
	int x;
	t_ast *temp;

	i = 0;
	c = 0;
	x = 1;
	if (ast == NULL)
		return ;
	if (ast->e_type == AST_VAR_EXP)
	{
		temp = init_ast(AST_WORD);
		while (ast->branches[c]->my_tok->e_type != TOK_WORD)
			c++;
		if (ast->branches[c] != NULL)
			temp->my_tok = init_token(ft_variable(shell, ast->branches[c]->my_tok->value), TOK_WORD);
		if (father)
		{
			while (father->branches[i]->e_type != AST_VAR_EXP)
				i++;
			ast_update(father, temp, i); 
			x = 0;
		}
	}
	i = 0;
	while (x && ast->branches && ast->branches[i] != NULL)
		replace_variables(shell, ast->branches[i++], ast);
}

char *ft_variable(t_shell *shell, char *str)
{
	int		where;
	float	var_set;

	var_set = var_is_set(shell, str);
	where = (int)var_set;
	if (var_set == -1)
		return (NULL);
	if (var_set - (float)where == 0)
	{
		// Then it is in vars
		return (ft_strdup(shell->vars[where + 1]));
	}
	return (expansion_from_envp(shell, where));
}

void ast_update(t_ast *parent, t_ast *child, int up)
{
	//printf("AST UPDATE\nup: %i\n", up);
	//printf("PARENT---------\n");
	//print_ast(parent, 0);
	//printf("CHILD---------\n");
	//print_ast(child, 0);

	int x;
	int i;
	t_ast **tree;

	i = 0;
	while (parent->branches && parent->branches[i] != NULL)
		i++;
	tree = malloc(sizeof(t_ast *) * (i + 1));
	if (!tree)
		return ;
	x = 0;
	while (x < i)
	{
		if (x != up)
			tree[x] = parent->branches[x];
		else
			tree[x] = child;
		x++;
	}
	tree[x] = NULL;
	if (up != -42)
	{
		clean_ast(parent->branches[up]);
	}
	if (parent->branches)
		free(parent->branches);
	parent->branches = tree;

	//print_ast(parent, 0);
	//print_ast(child, 0);
	//printf("->Left: ast_update_branch\n");
}

int variable_as_cmd(t_ast *root)
{
	int i;
	int x;

	i = 0;
	x = 0;
	while (root->branches[i] != NULL)
	{
		if (root->branches[i]->e_type == AST_WORD)
		{
			x = 1;
			root->branches[i]->e_type = AST_COMMAND;
			break ;
		}
		i++;
	}
	if (root->branches[i] && x == 1)
		if (root->branches[i]->my_tok && root->branches[i]->my_tok->value == NULL)
			return (1);
	return (0);
}
