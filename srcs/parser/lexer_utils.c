/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dareias- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 19:12:04 by dareias-          #+#    #+#             */
/*   Updated: 2021/11/22 12:41:09 by dareias-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_tok *token_switch(char c, t_lex *lex)
{
	if (lex->c == ';')
		return (init_token(";", TOK_SEMI));
	if (lex->c == '$')
		return (init_token("$", TOK_DOLLAR));
	if (lex->c == '(')
		return (init_token("(", TOK_OPAREN));
	if (lex->c == ')')
		return (init_token(")", TOK_CPAREN));
	if (lex->c == '/')
		return (init_token("/", TOK_BSLASH));
	if (lex->c == '.')
		return (init_token(".", TOK_COLLON));
	if (lex->c == '=')
		return (init_token("=", TOK_EQUALS));
	if (lex->c == '\'')
		return (init_token("\'", TOK_S_QUOTE));
	if (lex->c == '\"')
		return (init_token("\"", TOK_D_QUOTE));
	return (token_switch_two(c, lex));
}

t_tok *token_switch_two(char c, t_lex *lex)
{
	if (c == '<')
	{
		if (lex->src[lex->i + 1] == '<')
		{
			lex_next(lex);
			return (init_token("<<", TOK_ARROW_LEFT));
		}
		return (init_token("<", TOK_LT));
	}
	if (c == '>')
	{
		if (lex->src[lex->i + 1] == '>')
		{
			lex_next(lex);
			return (init_token(">>", TOK_ARROW_RIGHT));
		}
		return (init_token(">", TOK_GT));
	}
	return (NULL);
}

/*t_tok *lex_get_space(t_lex *lex)
{
	while (ft_isspace(lex->c))
		lex_next(lex);
	return (init_token(" ", TOK_SPACE));
}*/
/*t_tok *lex_get_optn(t_lex *lex)
{
	char	*value;
	int		i;
	int		x;

	i = 0;
	x = lex->i;
	while (ft_isalnum(lex->c))
	{
		i++;
		lex_next(lex);
	}
	value = ft_substr(lex->src, x, i);
	if (!value)
		return (NULL);
	return (init_token(value, TOK_OPTION));
}*/
