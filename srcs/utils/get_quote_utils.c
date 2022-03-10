/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_quote_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dareias- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 17:13:21 by dareias-          #+#    #+#             */
/*   Updated: 2022/03/09 17:13:24 by dareias-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*gnl_helper(char *holder, char *line, int ret)
{
	if (ret == 0 && !holder)
	{
		line = ft_strdup("");
		return (line);
	}
	if (ret == 0 && ft_strlen(holder) == ft_strchr('\n', holder))
	{
		if (ft_strlen(holder) == 0)
			return (NULL);
		line = ft_strdup(holder);
		free(holder);
		return (line);
	}
	holder = store_line(&line, holder, ret);
	if (!holder && ret == 0 && !line)
	{
		return (NULL);
	}
	return (line);
}

void	store_line_helper(char **line, char **holder, char *temp, int i)
{
	*line = ft_substr(*holder, 0, i + 1);
	temp = ft_substr(*holder, i + 1, ft_strlen(*holder));
	free(*holder);
	*holder = ft_strdup(temp);
	if (temp)
		free(temp);
}
