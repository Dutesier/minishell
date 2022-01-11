/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dareias- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 19:12:04 by dareias-          #+#    #+#             */
/*   Updated: 2022/01/11 18:53:42 by dareias-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_tok *token_switch(char c, t_lex *lex)
{
	if (lex->c == ';')
		return (init_token(";", TOK_SEMI));
	if (lex->c == '$')
		return (init_token("$", TOK_DOLLAR));
	/*if (lex->c == '(')
		return (init_token("(", TOK_OPAREN));
	if (lex->c == ')')
		return (init_token(")", TOK_CPAREN));*/
	if (lex->c == '~')
		return (init_token("~", TOK_TILDE));
	//if (lex->c == '/')
	//	return (init_token("/", TOK_BSLASH));
	if (lex->c == '|')
	{
		return (init_token("|", TOK_PIPE));
	}
	//if (lex->c == '.')
	//	return (init_token(".", TOK_DOT));
	if (lex->c == '=')
		return (init_token("=", TOK_EQUALS));
	/*if (lex->c == '\'')
		return (init_token("\'", TOK_S_QUOTE));
	if (lex->c == '\"')
		return (init_token("\"", TOK_D_QUOTE));*/
	if (lex->c == '\n')
		return (init_token("EOL", TOK_EOL));
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
	return (token_switch_three(lex));
}

t_tok *token_switch_three(t_lex *lex)
{
	int i;

	i = 0;
	while (ft_isspace(lex->c))
	{
		lex_next(lex);
		i++;
	}
	if (i == 0)
		return (NULL);
	lex->i--;
	lex->c = lex->src[lex->i];
	return (init_token(" ", TOK_SPACE));
}

int	nextquote(t_lex *lex, int q)
{
	int i;

	i = 0;
	lex->c = lex->src[lex->i];
	if (ft_isquote(lex->c) == q)
		return (i);
	while (ft_isquote(lex->c) != q && lex->c != '\0')
	{
		i++;
		lex_next(lex);
	}
	if (lex->c == '\0')
	{
		if (q == 1)
			get_quote(lex, '\''); //FIXME here we need a program that gets rest of str - probably good instance to use gnl
		else
			get_quote(lex, '\"'); //FIXME here we need a program that gets rest of str - probably good instance to use gnl
		return (i + nextquote(lex, q));
	}
	return (i);
}

char *ft_dupnoq(char *s)
{
	int i;
	int x;
	int inhib;
	char *sub;
	char *temp;

	i = 0;
	x = 0;
	temp = s;
	sub = malloc((ft_strlen(s) + 1) * sizeof(char));
	if (!sub)
		return (NULL);
	inhib = 0;
	while (s[x] != '\0')
	{
		if (s[x] == '\'')
			inhib = 1;
		if (s[x] == '\"')
			inhib = 2;
		if (inhib == 1)
		{
			if (s[x] == '\'')
			{
				inhib = 0;
				x++;
			}
			else
				sub[i++] = s[x++];	
		}
		else if (inhib == 2)
		{
			if (s[x] == '\"')
			{
				inhib = 0;
				x++;
			}
			else
				sub[i++] = s[x++];
		}
		else
			sub[i++] = s[x++];
	}
	sub[i] = '\0';
	free(temp);
	temp = malloc(sizeof(char) * i);
	while (i >= 0)
	{
		temp[i] = sub[i];
		i--;
	}
	free(sub);
	return (temp);
}

