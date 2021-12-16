/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dareias- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 15:14:15 by dareias-          #+#    #+#             */
/*   Updated: 2021/12/16 16:32:25 by dareias-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char *get_until(char *str);

char *ft_heredoc(t_comm *comm)
{
	int temp;
	char *str;
	char *t;

	t = ft_strcat(".mini.thd-", comm->heredoc);
	if (!t)
		return (0);
	temp = open(t, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (temp < 0)
		return (0);
	str = get_until(comm->heredoc);
	if (!str)
		return (0);
	write(temp, str, ft_strlen(str) * sizeof(char));
	free(str);
	close(temp);
	return (t);
}

static char *get_until(char *str)
{
	char *holder;
	char *needle;

	holder = get_next_line(STDIN_FILENO, "heredoc> ");
	needle = ft_strnstr(str, holder);
	if (!holder)
		return (NULL);
	while (!needle)
	{
		holder = ft_strcat(holder, get_next_line(STDIN_FILENO, "heredoc> "));
		if (!holder)
			return (NULL);
		needle = ft_strnstr(holder, str);
	}
	needle[0] = '\0';
	return (holder);
}
