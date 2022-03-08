/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_logic_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dareias- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 16:00:11 by dareias-          #+#    #+#             */
/*   Updated: 2022/03/07 22:48:26 by dareias-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_compound(t_par *par)
{
	if (par->tok->e_type == TOK_WORD)
		return (1);
	if (par->tok->e_type == TOK_SPACE)
		return (1);
	if (par->tok->e_type == TOK_OPTION)
		return (1);
	if (par->tok->e_type == TOK_DQUOTED)
		return (1);
	if (par->tok->e_type == TOK_DOT)
		return (1);
	if (par->tok->e_type == TOK_BSLASH)
		return (1);
	return (0);
}
