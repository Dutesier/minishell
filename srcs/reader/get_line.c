/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_line.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dareias- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 14:05:10 by dareias-          #+#    #+#             */
/*   Updated: 2021/11/18 14:11:53 by dareias-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *get_line(const char *prompt, char *line_read)
{
	if (line_read)
	{
		free(line_read);
		return (NULL);
	}
	line_read = readline(prompt);
	if (line_read && *line_read)
		add_history(line_read);
	return (line_read);
}
