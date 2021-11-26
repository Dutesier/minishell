/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_ast.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dareias- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 12:55:17 by dareias-          #+#    #+#             */
/*   Updated: 2021/11/26 13:29:28 by dareias-         ###   ########.fr       */
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
	int i;

	i = 0;
	if (!ast)
		return (0);
	while (ast->branches && ast->branches[i] != NULL)
	{
		if (ast->branches[i]->my_tok)
			clean_tok(ast->branches[i]->my_tok);
		free(ast->branches[i++]);
	}
	if (ast->branches)
		free(ast->branches);
	if (ast->my_tok)
		clean_tok(ast->my_tok);
	if (ast)
		free(ast);
	return (i);
}

int clean_parser(t_par *par)
{
	int i;

	i = 0;
	i = clean_lexer(par->lex);
	free(par);
	return (i);
}

int clean_lexer(t_lex *lex)
{
	free(lex);
	return (1);
}

int clean_tok(t_tok *tok)
{
	if (tok->e_type == TOK_WORD)
		free(tok->value);
	free(tok);
	return (1);
}
