/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_two.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dareias- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 16:17:06 by dareias-          #+#    #+#             */
/*   Updated: 2021/12/20 19:23:36 by dareias-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_isquote(int c)
{
	if (c == '\'')
		return (1);
	if (c == '\"')
		return (2);
	return (0);
}

int ft_isword(int c)
{
	if (ft_isquote(c) || ft_isalnum(c))
		return (1);
	if (c == '.' || c == '/' || c == '-' || c ==  '_')
		return (1);
	return (0);
}

int ft_isforb(int c)
{
	if (ft_isspace(c))
		return (1);
	if (ft_strchr(c, "<>$=;") > -1)
		return (1);
	if (c == '\0')
		return (1);
	return (0);
}

int ft_iscomm(char *str)
{
	if (ft_strcmp(str, "cd", ft_min(ft_strlen(str), 2)))
		return (1);
	if (ft_strcmp(str, "pwd", ft_min(ft_strlen(str), 3)))
		return (2);
	if (ft_strcmp(str, "echo", ft_min(ft_strlen(str), 4)))
		return (3);
	if (ft_strcmp(str, "env", ft_min(ft_strlen(str), 3)))
		return (4);
	if (ft_strcmp(str, "export", ft_min(ft_strlen(str), 6)))
		return (5);
	if (ft_strcmp(str, "unset", ft_min(ft_strlen(str), 5)))
		return (6);
	return (0);
}
