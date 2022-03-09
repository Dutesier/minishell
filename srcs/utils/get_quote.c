/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_quote.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dareias- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 16:50:07 by dareias-          #+#    #+#             */
/*   Updated: 2022/02/11 08:37:18 by dareias-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*store_buffer(char *holder, char *buff)
{
	char	*temp;

	if (holder)
	{
		temp = ft_strjoin(holder, buff);
		free(holder);
		holder = ft_strdup(temp);
		free(temp);
	}
	else
	{
		holder = ft_strdup(buff);
		if (holder == NULL)
			return (NULL);
	}
	return (holder);
}

char	*store_line(char **line, char *holder, int ret)
{
	int		i;
	int		len;

	i = 0;
	if (!holder)
		return (NULL);
	len = ft_strlen(holder);
	while (holder[i] != '\0')
	{
		if (holder[i] == '\n')
			break ;
		i++;
	}
	if (i < len)
		store_line_helper(line, holder, NULL, i);
	else if (ret == 0)
	{
		if (!len)
			return (NULL);
		*line = holder;
		holder = NULL;
	}
	return (holder);
}

char	*get_next_line(int fd, char *s)
{
	static char	*holder[1024];
	char		buff[421];
	char		*line;
	int			ret;

	if (fd < 0 || read(fd, holder[fd], 0) < 0)
		return (NULL);
	ret = 1;
	line = NULL;
	if (s)
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
	return (gnl_helper(holder[fd], line, ret));
}

int	get_quote(t_lex *lex, char q)
{
	char	*holder;
	char	*s;

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
