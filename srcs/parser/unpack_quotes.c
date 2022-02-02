/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unpack_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dareias- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 16:03:09 by dareias-          #+#    #+#             */
/*   Updated: 2022/01/21 19:22:20 by dareias-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int unpack_quotes(t_ast *ast)
{
	int i;
	int ret;

	i = 0;
	ret = 0;
	while (ast && ast->branches && ast->branches[i] != NULL)
	{
		unpack_quotes(ast->branches[i]);
		if (ast->branches[i]->my_tok && ast->branches[i]->my_tok->e_type == TOK_DQUOTED)
			ret += expand_quote(ast, i);
		i++;
	}
	return (ret);
}

int expand_quote(t_ast *father, int i)
{
	int j;
	int found_dollar;
	t_ast *son;
	char *value;

	j = 0;
	found_dollar = 0;
	son = father->branches[i];
	value = son->my_tok->value;	
	while (value[j] != '\0')
	{
		if (value[j] == '$')
		{
			found_dollar = 1;
			break ;
		}
		j++;
	}
	if (found_dollar)
		return (exp_needed(father, i, value, j));
	return (no_exp_needed(son, value));
}

// exp stands for expansion

int no_exp_needed(t_ast *son, char *value)
{
	t_tok *temp;

	temp = init_token(value, TOK_WORD);
	clean_tok(son->my_tok);
	son->my_tok = temp;
	return (1);
}

int exp_needed(t_ast *father, int son_i, char *value, int j)
{
	int i;
	int a;
	t_tok *temp_t;
	t_ast *temp_a;
	char *holder;

	i = 0;
	a = 0;
	holder = ft_dupnoq(value);

	// Store up to the variable
	if (holder[0] != '$')
	{
		temp_t = init_token(ft_substr(holder, 0, j), TOK_WORD);
		clean_tok(father->branches[son_i]->my_tok);
		father->branches[son_i]->my_tok = temp_t;
		a++;
	}
	else
		j++;

	// Store the VAR EXPANSION
	temp_a = init_ast(AST_VAR_EXP);
	temp_a = add_var_exp(temp_a, holder, j++);
	if (a)
		ast_add_branch_idx(father, temp_a, ast_branch_ammount(father), son_i + a); 
	else
	{
		clean_ast(father->branches[son_i]);
		father->branches[son_i] = temp_a;
		a++;
	}


	// Checking if there is more to store 
	while (holder[j + i] != '\0')
		if (holder[j + (i++)] == ' ') // or also some other chars!!
			break ;
	if (holder[j + i] == '\0')
	{
		free(holder);
		free(value);
		return (2); // for two branches added
	}
	j = j + i;
	i = 0;
	while (holder[j + i] != '\0')
		i++;
	temp_a = init_ast(AST_WORD);
	temp_t = init_token(ft_substr(holder, j, i), TOK_WORD);
	temp_a->my_tok = temp_t;
	ast_add_branch_idx(father, temp_a, ast_branch_ammount(father), son_i + a); 
	free(holder);
	free(value);
	return (3);
}

t_ast *add_var_exp(t_ast *ast, char *value, int j)
{
	int		i;
	char	*temp_s;
	t_ast	*temp_a;
	t_tok	*temp_t;

	i = 0;
	temp_t = init_token(ft_strdup("$"), TOK_DOLLAR);
	if (value[j] == '$')
		j++;
	temp_a = init_ast(AST_WORD);
	temp_a->my_tok = temp_t;
	ast_add_branch(ast, temp_a, 0);
	while (value[j + i] != '\0')
		if (value[j + (i++)] == ' ') // Some other chars too probably
		{
			i--;
			break ;
		}
	temp_s = ft_substr(value, j, i); 
	printf("STRLEN: %i\n", ft_strlen(temp_s));
	temp_t = init_token(temp_s, TOK_WORD);
	temp_a = init_ast(AST_WORD);
	temp_a->my_tok = temp_t;
	ast_add_branch(ast, temp_a, 1);
	return (ast);
}

