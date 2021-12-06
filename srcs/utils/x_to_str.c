/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   x_to_str.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dareias- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 13:45:25 by dareias-          #+#    #+#             */
/*   Updated: 2021/12/06 15:41:03 by dareias-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *tok_to_str(unsigned int type)
{
	if (type == TOK_WORD)
		return ("TOK_WORD");
	if (type == TOK_DOLLAR)
		return ("TOK_DOLLAR");
	if (type == TOK_LT)
		return ("TOK_LT");
	if (type == TOK_GT)
		return ("TOK_GT");
	if (type == TOK_ARROW_RIGHT)
		return ("TOK_ARROW_RIGHT");
	if (type == TOK_ARROW_LEFT)
		return ("TOK_ARROW_LEFT");
	if (type == TOK_OPTION)
		return ("TOK_OPTION");
	if (type == TOK_S_QUOTE)
		return ("TOK_S_QUOTE");
	if (type == TOK_D_QUOTE)
		return ("TOK_D_QUOTE");
	if (type == TOK_SEMI)
		return ("TOK_SEMI");
	if (type == TOK_DOT)
		return ("TOK_DOT");
	if (type == TOK_EQUALS)
		return ("TOK_EQUALS");
	if (type == TOK_BSLASH)
		return ("TOK_BSLASH");
	if (type == TOK_OPAREN)
		return ("TOK_OPAREN");
	if (type == TOK_CPAREN)
		return ("TOK_CAPREN");
	if (type == TOK_SPACE)
		return ("TOK_SPACE");
	if (type == TOK_PIPE)
		return ("TOK_PIPE");
	if (type == TOK_EOL)
		return ("TOK_EOL");
	return ("TOKEN UNDEFINED");
}

char *ast_to_str(unsigned int type)
{
	if (type == AST_ROOT)
		return ("AST_ROOT");
	if (type == AST_COMPOUND)
		return ("AST_COMPOUND");
	if (type == AST_VARIABLE)
		return ("AST_VARIABLE");
	if (type == AST_COMMAND)
		return ("AST_COMMAND");
	if (type == AST_WORD)
		return ("AST_WORD");
	if (type == AST_VAR_DEF)
		return ("AST_VAR_DEF");
	if (type == AST_COMM_ARGS)
		return ("AST_COMM_ARGS");
	if (type == AST_NULL)
		return ("AST_NULL");
	return ("AST not defined");
}
