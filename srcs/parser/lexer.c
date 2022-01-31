/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dareias- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Updated: 2022/01/21 16:13:47 by dareias-         ###   ########.fr       */
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
	lex->q = 0;
	return (lex);
}

void lex_next(t_lex *lex)
{
	if (lex->i < lex->size && lex->c != '\0')
	{
		lex->i++;
		lex->c = lex->src[lex->i];
	}
	else
		printf("*** ERROR: lex->i %i not < then lex->size %i or lex->c %c = NTR\n", lex->i, lex->size, lex->c);
}

t_tok *lex_get_word(t_lex *lex)
{
	char	*value;
	int		i;
	int		x;
	int		q;
	int     store;

	i = 0;
	x = lex->i;
	store = 0;
	while (!ft_isforb(lex->c))
	{
		q = ft_isquote(lex->c);
		if (q > 0)
		{
			i++;
			lex_next(lex);
			store = q;
			q = nextquote(lex, q); // REUSING Q for a whole diff thing
			if (q > 0)
				i += q - 1;
		}
		i++;
		lex_next(lex);
	}
	value = ft_dupnoq(ft_substr(lex->src, x, i));
	if (!value)
	{	
		lex_next(lex);
		return (init_token(NULL, TOK_ERROR));
	}
	if (store == 2)
		return (init_token(value, TOK_DQUOTED));
	return (init_token(value, TOK_WORD));
}

t_tok *next_token(t_lex *lex)
{
	t_tok	*tok;

	while (lex->c != '\0')
	{
		tok = token_switch(lex->c, lex);
		if (tok)
		{
			lex_next(lex);
			return (tok);
		}
		else
		{
			return (lex_get_word(lex));
		}
	}
	return (init_token(NULL, TOK_EOL));
}

