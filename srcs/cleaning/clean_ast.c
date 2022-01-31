/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_ast.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dareias- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 12:55:17 by dareias-          #+#    #+#             */
/*   Updated: 2022/01/31 17:58:18 by dareias-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 *
 * When freeing tokens: make sure we free every single one that we dont use (while parsing)!
 * free the ones that we do;
 *
 */

int	clean_ast(t_ast *ast)
{
	//printf("Cleaning AST...\n");
	int i;

	i = 0;
	if (!ast)
		return (0);
	while (ast->branches && ast->branches[i] != NULL)
		clean_ast(ast->branches[i++]);
	if (ast->branches)
		free(ast->branches);
	if (ast->my_tok)
		clean_tok(ast->my_tok);
	if (ast)
		free(ast);
	//printf("Cleaned AST\n");
	return (i);
}

int clean_parser(t_par *par)
{
	//printf("Cleaning parser...\n");
	int i;

	i = 0;
	i = clean_lexer(par->lex);
	free(par);
	//printf("Cleaned parser\n");
	return (i);
}

int clean_lexer(t_lex *lex)
{
	//printf("Cleaning lexer\n");
	free(lex);
	//printf("Cleaned lexer\n");
	return (1);
}

int clean_tok(t_tok *tok)
{
	//printf("Cleaning token %s (%p) %s\n", tok_to_str(tok->e_type), &tok->value, tok->value);
	if (tok->e_type == TOK_WORD)
		free(tok->value);
	free(tok);
	//printf("Cleaned token\n");
	return (1);
}
