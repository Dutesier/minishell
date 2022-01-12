/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dareias- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 15:34:57 by dareias-          #+#    #+#             */
/*   Updated: 2022/01/12 19:39:21 by dareias-         ###   ########.fr       */
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
	printf("New lexer\n");
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
	int     store;

	i = 0;
	x = lex->i;
	store = lex->q;
	printf("\n-->[LEX_GET_WORD] Current str: %s\n", lex->src+lex->i);
	printf("-->[LEX_GET_WORD] lex->q %i\n", lex->q);
	while (!ft_isforb(lex->c))
	{
		printf("Lex->c %c\n", lex->c);
		q = ft_isquote(lex->c);
		if (q > 0 || lex->q == 2) // If we're on a quote or if we left one open
		{
			if (lex->q && q > 1) // Meaning we were hoping for a " to close and we got it
			{
				i++;
				lex_next(lex);
				break ;
			}

			if (lex->q == 2) // Because we're gonna get the nextquote
				lex->q = 0;

			i++;
			lex_next(lex);
			q = nextquote(lex, q);
			if (q > 0)
			{
				if (lex->q == 1)
				{
					i += q;
					break ;
				}
				else
					i += q - 1;
			}
		}
		i++;
		lex_next(lex);
	}
	if (lex->q == 1 && store == 1)
		lex->q = 2;
	printf("-->[LEX_GET_WORD] lex->q %i\n", lex->q);
	printf("-->[LEX_GET_WORD] Rest of str: %s\n", lex->src+x);
	value = ft_dupnoq(ft_substr(lex->src, x, i));
	printf("-->[LEX_GET_WORD] Store str: %s\n", value);
	if (!value)
	{	
		lex_next(lex);
		return (init_token(NULL, TOK_ERROR));
	}
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
		/*
		if (ft_isword(lex->c))
		{
			return (lex_get_word(lex)); 
		}
		tok = token_switch(lex->c, lex);
		lex_next(lex);
		if (tok)
		{
			return (tok);
		}
		return (init_token(NULL, TOK_ERROR));*/
	}
	if (lex->q)
	{
		return (unclosed_quote(lex));
	}
	return (init_token(NULL, TOK_EOL));
}

