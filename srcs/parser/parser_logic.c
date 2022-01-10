/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_logic.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dareias- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 10:58:17 by dareias-          #+#    #+#             */
/*   Updated: 2021/12/30 18:36:01 by dareias-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ast *parse_compound(t_par *par)
{
	//printf("Entered: parse_compound\n");
	t_ast *ast;
	int i;
	int x;
	unsigned int next;

	i = 0;
	x = 0;
	ast = init_ast(AST_COMPOUND);
	next = par->tok->e_type;
	if (command_tok(next) == 2)
	{
		x++;
		ast_add_branch(ast, parse_redirect(par), i++);
	}
	else
	{
		ast_add_branch(ast, parse_word(par), i++);
		printf("Calling parser_next from parse compound\n"); parser_next(par, 42);
	}
	next = par->tok->e_type;
	if (next == TOK_EQUALS)
	{
		ast->branches[0]->e_type = AST_VARIABLE;
		ast_add_branch(ast, parse_variable(par), i++);
		next = par->tok->e_type;
		if (next == TOK_SPACE)
		{
			free(par->tok);
			printf("Calling parser_next from parse compound\n"); parser_next(par, 42);
			next = par->tok->e_type;
		}
		if (next == TOK_SEMI || next == TOK_EOL)
			return (ast);
	}
	if (next == TOK_SEMI || next == TOK_EOL)
	{
		if (i == 1)
			ast->branches[0]->e_type = AST_COMMAND; //FIXME: What happens when a var expansion happens first??? It is getting set to COMMAND
		return (ast);
	}
	else
	{
		i += command_parser(ast, par, i, x);
		//printf("Exited parse_compound\n");
		return (ast);
	}
	return (ast); // FIXME Should null terminate? 
}


t_ast *parse_redirect(t_par *par)
{
	t_ast			*ast;
	int				i;
	unsigned int	next;

	//printf("Entered: parse_redirect\n");
	ast = init_ast(AST_REDIRECT);
	i = 0;
	next = par->tok->e_type;
	ast_add_branch(ast, parse_word(par), i++); // The redirect Token
	printf("Calling parser_next from parse redirect\n"); parser_next(par, 42);
	next = par->tok->e_type;
	if (next == TOK_SPACE)
	{
		ast_add_branch(ast, parse_word(par), i++);
		printf("Calling parser_next from parse redirect\n"); parser_next(par, 42);
		next = par->tok->e_type;
	}
	ast_add_branch(ast, parse_word(par), i++); // The file to redirect to or from
	printf("Calling parser_next from parse redirect\n"); parser_next(par, 42);
	next = par->tok->e_type;
	if (next == TOK_SPACE)
	{
		ast_add_branch(ast, parse_word(par), i++);
		printf("Calling parser_next from parse redirect\n"); parser_next(par, 42);
	}
	return (ast);
}

