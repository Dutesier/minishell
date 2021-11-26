/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dareias- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 15:34:57 by dareias-          #+#    #+#             */
/*   Updated: 2021/11/26 19:00:20 by dareias-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_tok *init_token(char *value, int type)
{
	t_tok *tok;
	tok = malloc(sizeof(t_tok));
	if (!tok)
		return (NULL);
	tok->value = value;
	tok->e_type = type;
	printf("Initialized token [%s] for %s\n", tok_to_str(tok->e_type), value);
	return (tok);
}

t_lex *init_lexer(char *src)
{
	t_lex *lex;

	lex = malloc(sizeof(t_lex));
	if (!lex)
		return (NULL);
	lex->i = 0;
	lex->c = src[lex->i];
	lex->src = src;
	lex->size = ft_strlen(src);
	return (lex);
}

void lex_next(t_lex *lex)
{
	if (lex->i < lex->size && lex->c != '\0')
	{
		lex->i++;
		lex->c = lex->src[lex->i];
	}
}

t_tok *lex_get_word(t_lex *lex)
{
	char	*value;
	int		i;
	int		x;
	int		q;

	i = 0;
	x = lex->i;
	while (ft_isalnum(lex->c) || ft_isquote(lex->c))
	{
		q = ft_isquote(lex->c);
		if (q > 0)
		{
			i++;
			lex_next(lex);
			i += nextquote(lex, q);
		}
		i++;
		lex_next(lex);
	}
	value = ft_substr(lex->src, x, i);
	if (!value)
		return (NULL);
	return (init_token(value, TOK_WORD));
}

t_tok *next_token(t_lex *lex)
{
	t_tok *tok;

	while (lex->c != '\0')
	{
		if (ft_isalnum(lex->c) || ft_isquote(lex->c))
			return (lex_get_word(lex)); 
		tok = token_switch(lex->c, lex);
		if (tok)
		{
			lex_next(lex);
			return (tok);
		}
	}
	return (init_token(NULL, TOK_EOL));
}

