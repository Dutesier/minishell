/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dareias- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 15:14:15 by dareias-          #+#    #+#             */
/*   Updated: 2021/12/30 15:00:02 by dareias-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char *get_until(char *str);

char *ft_heredoc(t_comm *comm)
{
	int temp;
	char *str;
	char *t;

	t = ft_strdup(".mini.thd");
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
	if (close(temp) < 0)
		DEBUG(fprintf(stderr, "Could not close HEREDOC (%i)\n", temp));
	return (t);
}

static char *get_until(char *str)
{
	char *holder;
	char *needle;
	int		i;

	i = 0;
	holder = get_next_line(STDIN_FILENO, "heredoc> ");
	//printf("->str[3] %i<-\n", (int)str[3]);
	if (ft_isspace(str[ft_strlen(str) - 1]))
		str[ft_strlen(str) - 1] = '\0';
	needle = ft_strnstr(holder, str);
	if (!holder)
		return (NULL);
	while (!needle)
	{
		i = 1;
		holder = ft_strcat(holder, get_next_line(STDIN_FILENO, "heredoc> "));
		if (!holder)
			return (NULL);
		needle = ft_strnstr(holder, str);
	}
	if (i)
		needle[0] = '\0';
	return (holder);
}
