/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dareias- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 10:38:21 by dareias-          #+#    #+#             */
/*   Updated: 2022/03/07 23:33:06 by dareias-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_par *init_parser(t_lex *lex)
{
	t_par *par;

	par = malloc_or_exit(sizeof(t_par));
	par->lex = lex;
	par->tok = next_token(lex);
	par->next = par->tok->e_type;
	return (par);
}

t_tok *parser_next(t_par *par, unsigned int type)
{
	//DEBUG(fprintf(stderr, "Previous Token: [%s] (%s)\nGetting next token...\n", tok_to_str(par->tok->e_type), par->tok->value));
	par->tok = next_token(par->lex);
	par->next = par->tok->e_type;
	//DEBUG(fprintf(stderr, "New Token: [%s] (%s)\n", tok_to_str(par->tok->e_type), par->tok->value));
	if (par->tok->e_type != type && type != 42)
	{
		return (NULL);
	}
	return (par->tok);

}

t_ast *parse_to_ast(t_par *par)
{
	t_ast *root;
	int i;

	i = 0;
	root = init_ast(AST_ROOT);
	if (wordquotetok(par->tok->e_type) || command_tok(par->tok->e_type) == 2)
		ast_add_branch(root, parse_compound(par), i++);
	while (par->tok->e_type != TOK_EOL)
	{
		while (par->tok->e_type == TOK_SEMI || par->tok->e_type == TOK_SPACE)
		{
			free(par->tok);
			parser_next(par, 42);
		}
		if (par->tok->e_type == TOK_PIPE)
		{
			ast_add_branch(root, parse_word(par), i++);
			parser_next(par, 42);
		}
		while (par->tok->e_type == TOK_SEMI || par->tok->e_type == TOK_SPACE)
		{
			free(par->tok);
			parser_next(par, 42);
		}
		if (par->tok->e_type != TOK_EOL  &&  par->tok->e_type != TOK_SEMI)
			ast_add_branch(root, parse_compound(par), i++);
	}
	free(par->tok); //Freeing the TOK_EOL
	return (root);
}

t_ast *parse_word(t_par *par)
{
	t_ast *ast;

	if (par->tok->e_type == TOK_DOLLAR && !parse_exp_status(par))
		return (parse_expansion(par));

	ast = init_ast(AST_WORD);
	ast->branches = NULL;
	ast->my_tok = par->tok;
	return (ast);
}

t_ast *parse_variable(t_par *par)
{
	t_ast *ast;
	int i;
	
	i = 0;
	ast = init_ast(AST_VAR_DEF);
	ast_add_branch(ast, parse_word(par), i++); // The EQUALS
	parser_next(par, 42);
	ast_add_branch(ast, parse_word(par), i++); // The var value
	parser_next(par, 42);
	// Right now,  Variable AST has a word->equals and a word->variable.value

	return (ast);
}
