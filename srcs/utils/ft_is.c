/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dareias- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 17:47:52 by dareias-          #+#    #+#             */
/*   Updated: 2021/11/19 17:54:22 by dareias-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int is_spec(char c)
{
	if (c == '|' || c == '<' || c == '>')
		return (1);
	return (0);
}

int	ft_isalpha(int c)
{
	return (((65 <= c) && (90 >= c)) || ((97 <= c) && (122 >= c)));
}

int	ft_isdigit(int c)
{
	return (c >= 48 && c <= 48 + 9);
}

int	ft_isalnum(int c)
{
	return (ft_isdigit(c) + ft_isalpha(c));
}
