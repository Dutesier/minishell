/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_logic.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dareias- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 10:58:17 by dareias-          #+#    #+#             */
/*   Updated: 2021/12/07 12:09:42 by dareias-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int command_tok(unsigned int type);

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
		next = par->tok->e_type;
		if (command_tok(next) == 2)
		{
			ast_add_branch(ast, parse_redirect(par), i++);
			next = par->tok->e_type;
			
		}
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
	while (!command_tok(next))
	{
		ast_add_branch(ast, parse_word(par), i++);
		parser_next(par, 42);
		next = par->tok->e_type;
	}
	// FIXME add redirects
	return (ast);
}

t_ast *parse_redirect(t_par *par)
{
	t_ast			*ast;
	int				i;
	unsigned int	next;

	ast = init_ast(AST_REDIRECT);
	i = 0;
	next = par->tok->e_type;
	ast_add_branch(ast, parse_word(par), i++); // The redirect Token
	parser_next(par, 42);
	next = par->tok->e_type;
	if (next == TOK_SPACE)
	{
		ast_add_branch(ast, parse_word(par), i++);
		parser_next(par, 42);
	}
	ast_add_branch(ast, parse_word(par), i++); // The file to redirect to or from
	parser_next(par, 42);
	return (ast);
}

static int command_tok(unsigned int type)
{
	if (type == TOK_EOL || type == TOK_SEMI || type == TOK_PIPE)
		return (1);
	if (type == TOK_GT || type == TOK_LT || type == TOK_ARROW_RIGHT || type == TOK_ARROW_LEFT)
		return (2);
	return (0);
}
