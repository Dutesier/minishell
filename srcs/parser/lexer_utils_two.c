/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils_two.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dareias- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 18:44:08 by dareias-          #+#    #+#             */
/*   Updated: 2022/01/12 19:33:32 by dareias-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_tok *unclosed_quote(t_lex *lex)
{
	int		i;
	char	*value;

	i = 0;
	i += nextquote(lex, 2);
	value = ft_dupnoq(ft_substr(lex->src, lex->i, i));
	lex->q = 0;
	return (init_token(value, TOK_WORD));
}
