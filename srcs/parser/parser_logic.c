/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_logic.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dareias- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 10:58:17 by dareias-          #+#    #+#             */
/*   Updated: 2021/11/24 14:25:14 by dareias-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ast *parse_compound(t_par *par)
{
	//printf("Entered: parse_compound\n");
	t_ast *ast;
	int i;
	unsigned int next;

	i = 0;
	ast = init_ast(AST_COMPOUND);
	ast_add_branch(ast, parse_word(par), i++);
	parser_next(par, 42);
	next = par->tok->e_type;
	if (next == TOK_EQUALS)
	{
		ast_add_branch(ast, parse_variable(par), i++);
		return (ast);
	}
	if (next == TOK_SPACE)
	{
		ast_add_branch(ast, parse_command(par), i++);
		return (ast);
	}
	if (next == TOK_SEMI || next == TOK_EOL)
		return (ast);
	return (ast); // FIXME Should null terminate? 
}

t_ast *parse_command(t_par *par)
{
	//printf("Entered: parse_command\n");
	t_ast *ast;
	int i;
	unsigned int next;

	i = 0;
	ast = init_ast(AST_COMMAND);
	next = par->tok->e_type;
	while (next == TOK_WORD || next == TOK_SPACE)
	{
		ast_add_branch(ast, parse_word(par), i++);
		if (par->tok->e_type == TOK_WORD)
			parser_next(par, TOK_SPACE);
		else
			parser_next(par, TOK_WORD);
		next = par->tok->e_type;
	}
	// FIXME add redirects
	if (next == TOK_SEMI || next == TOK_EOL)
		return (ast);
	if (next == TOK_PIPE)
	{
		ast_add_branch(ast, parse_word(par), i++);
		parser_next(par, TOK_PIPE);
		ast_add_branch(ast, parse_command(par), i++);
	}
	return (ast);
}
