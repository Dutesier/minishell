/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable_expansion.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dareias- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 15:36:06 by dareias-          #+#    #+#             */
/*   Updated: 2021/12/17 20:09:36 by dareias-         ###   ########.fr       */
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
	printf("Replacing variables ---- AST: %s\n", ast_to_str(ast->e_type));
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
	printf("good\n");
	while (x && ast->branches && ast->branches[i] != NULL)
		replace_variables(shell, ast->branches[i++], ast);
	printf("left rep variables\n");
}

char *ft_variable(t_shell *shell, char *str)
{
	int i;

	i = 0;
	while (shell->vars[i] != NULL)
	{
		if (ft_strcmp(str, shell->vars[i], ft_min(ft_strlen(str), ft_strlen(shell->vars[i]))))
			return (shell->vars[i + 1]);
		i = i + 2;
	}
	return (NULL);
}

void ast_update(t_ast *parent, t_ast *child, int up)
{
	/*int b = 0;
	while (parent->branches && parent->branches[b] != NULL)
	{
		printf("-----Parent %s starts with ->%s<- \n", ast_to_str(parent->e_type), parent->branches[b++]->my_tok->value);
	}*/

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
		{
			tree[x] = child;
		}
		x++;
	}
	tree[x] = NULL;
	if (up != -42)
		clean_ast(parent->branches[up]);
	if (parent->branches)
		free(parent->branches);
	parent->branches = tree;

/*	i = 0;
	while (parent->branches && parent->branches[i] != NULL)
	{
		printf("-----Added ->%s<- to the parents %s branches\n", parent->branches[i++]->my_tok->value, ast_to_str(parent->e_type));
	}*/
	printf("->Left: ast_update_branch\n");
}
