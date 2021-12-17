/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_expansion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dareias- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 15:13:37 by dareias-          #+#    #+#             */
/*   Updated: 2021/12/17 15:27:30 by dareias-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ast *parse_var_exp(t_par *par); // to stop recursiveness

t_ast *parse_expansion(t_par *par)
{
	t_ast	*ast;
	int		i;

	i = 0;
	ast = init_ast(AST_VAR_EXP);
	ast_add_branch(ast, parse_var_exp(par), i++); // The Dollar sign
	parser_next(par, TOK_WORD);
	ast_add_branch(ast, parse_var_exp(par), i++); // The word after the sign
	parser_next(par, 42);

	return (ast);
}

t_ast *parse_var_exp(t_par *par) // to stop recursiveness
{
	t_ast *ast;
	// int i;
	// i = 0;


	ast = init_ast(AST_WORD);
	ast->branches = NULL;
	ast->my_tok = par->tok;
	return (ast);
}
