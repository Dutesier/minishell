/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_quote.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dareias- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 16:50:07 by dareias-          #+#    #+#             */
/*   Updated: 2021/12/16 15:49:24 by dareias-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *store_buffer(char *holder, char *buff)
{
	char *temp;

	if (holder)
	{
		temp = ft_strjoin(holder, buff);
		free(holder);
		holder = ft_strdup(temp);
		free(temp);
	}
	else
	{
		holder = ft_strdup(buff); // if holder == NULL it means we had a file with no nl ?
		if (holder == NULL)
			return (NULL);
	}
	return (holder);
}

char *store_line(char **line, char *holder, int ret)
{
	char	*temp;
	int		i;

	i = 0;
	if (!holder)
		return (NULL);
	while (holder[i] != '\0')
	{
		if (holder[i] == '\n')
			break ;
		i++;
	}

	if (i < ft_strlen(holder)) // If we got here cause there's a nl somewhere in holder
	{
		*line = ft_substr(holder, 0, i + 1);
		temp = ft_substr(holder, i + 1, ft_strlen(holder));
		free(holder);
		holder = ft_strdup(temp);
		if (temp)
			free(temp);
	}
	else if (ret == 0) // if we've read till EOF
	{
		if (holder[0] == '\0') //for the possibility of a file with no nl!!
			return (NULL);
		*line = holder;
		holder = NULL;
	}
	return (holder);
}

char *get_next_line(int fd, char *s)
{
	static char	*holder[1024];
	char		buff[420 + 1];
	char		*line;
	int			ret;

	if (fd < 0 || read(fd, holder[fd], 0) < 0)
		return (NULL);

	ret = 1;
	ft_putstr_fd(s, 1);
	while (ret > 0)
	{
		ret = read(fd, buff, 420);
		if (ret < 0)
			return (NULL);

		buff[ret] = '\0';

		holder[fd] = store_buffer(holder[fd], buff);

		if (ft_strchr('\n', buff) > -1)
			break ;
	}

	if (ret == 0 && !holder[fd]) // Edge case: file with just EOF
	{
		line = ft_strdup("");
		return (line);
	}

	if (ret == 0 && ft_strlen(holder[fd]) == ft_strchr('\n', holder[fd])) // Edge case: read till end of file but:
	{
		if (ft_strlen(holder[fd]) == 0) // Either it was just an empty file
			return (NULL);

		// Or it was a file that ended in a nl
		line = ft_strdup(holder[fd]);
		free(holder[fd]);
		return (line);
	}

	holder[fd] = store_line(&line, holder[fd], ret);

	if (!holder[fd] && ret == 0 && !line)
		return (NULL);

	return (line);
}

int get_quote(t_lex *lex, char q)
{
	char *holder;
	char *s;

	if (q == '\'')
		s = "quote> ";
	else if (q == '\"')
		s = "dquote> ";
	else
		s = "pipe> ";
	holder = get_next_line(STDIN_FILENO, s);
	if (!holder)
		return (1);
	while (ft_strchr(q, holder) < 0)
	{
		holder = ft_strcat(holder, get_next_line(STDIN_FILENO, s));
		if (!holder)
			return (1);
	}
	holder = ft_strcat(lex->src, holder);
	free(lex->src);
	lex->src = holder;
	lex->size = ft_strlen(holder);
	return (0);
}
