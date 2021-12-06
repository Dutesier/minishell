/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_logic.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dareias- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 10:58:17 by dareias-          #+#    #+#             */
/*   Updated: 2021/12/06 15:38:42 by dareias-         ###   ########.fr       */
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
		ast->branches[0]->e_type = AST_VARIABLE;
		ast_add_branch(ast, parse_variable(par), i++);
		next = par->tok->e_type;
		if (next == TOK_SPACE)
		{
			free(par->tok);
			parser_next(par, 42);
			next = par->tok->e_type;
		}
		if (next == TOK_SEMI || next == TOK_EOL)
			return (ast);
	}
	if (next == TOK_SEMI || next == TOK_EOL)
	{
		if (i == 1)
			ast->branches[0]->e_type = AST_COMMAND;
		return (ast);
	}
	else
	{
		ast->branches[0]->e_type = AST_COMMAND;
		ast_add_branch(ast, parse_command(par), i++);
		return (ast);
	}
	return (ast); // FIXME Should null terminate? 
}

t_ast *parse_command(t_par *par)
{
	//printf("Entered: parse_command\n");
	t_ast *ast;
	int i;
	unsigned int next;

	i = 0;
	ast = init_ast(AST_COMM_ARGS);
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
