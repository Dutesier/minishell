/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dareias- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 17:31:26 by dareias-          #+#    #+#             */
/*   Updated: 2021/11/17 19:51:36 by dareias-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int ft_putchar_fd(char c, int fd)
{
	if (fd < 0)
		return (0);
	return (write(fd, &c, 1));
}

int ft_putstr_fd(char *s, int fd)
{
	int i;

	i = 0;
	if (!s || fd < 0)
		return (0);
	while (s[i] != '\0')
		ft_putchar_fd(s[i++], fd);
	return (i);
}
