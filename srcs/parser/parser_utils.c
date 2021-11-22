/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dareias- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 10:38:21 by dareias-          #+#    #+#             */
/*   Updated: 2021/11/22 20:03:35 by dareias-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_par *init_parser(t_lex *lex)
{
	//printf("Entered: init_parser\n");
	t_par *par;

	par = malloc(sizeof(t_par));
	if (!par)
		return (NULL);
	par->lex = lex;
	par->tok = next_token(lex);
	return (par);
}

t_tok *parser_next(t_par *par, unsigned int type)
{
	par->tok = next_token(par->lex);
	if (par->tok->e_type != type)
	{
		printf("[Parser] Wrong node %d, was expecting %d\n", par->tok->e_type, type);
		return (NULL);
	}
	return (par->tok);

}

t_ast *parse_to_ast(t_par *par)
{
	//printf("Entered: parse_to_ast\n");
	if (par->tok->e_type == TOK_WORD)
		return (parse_variable(par)); // Here is the main entry point into parssing
	return (init_ast(AST_NULL));
}

t_ast *parse_word(t_par *par)
{
	t_ast *ast;
	int i;
	i = 0;

	ast = init_ast(AST_WORD);
	ast->branches = NULL;
	ast->my_tok = par->tok;
	return (ast);
}

t_ast *parse_variable(t_par *par)
{
	//printf("Entered: parse_variable\n");
	t_ast *ast;
	int i;
	
	i = 0;
	ast = init_ast(AST_VARIABLE);
	ast_add_branch(ast, parse_word(par), i++);
	parser_next(par, TOK_EQUALS);
	ast_add_branch(ast, parse_word(par), i++);
	parser_next(par, TOK_WORD);
	ast_add_branch(ast, parse_word(par), i++);
	/*i = 0;
	while (ast->branches[i] != NULL)
	{
		printf("AST: %i\n", ast->e_type);
	}*/
	return (ast);
}






