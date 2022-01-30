/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_line.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jibanez- <jibanez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 14:05:10 by dareias-          #+#    #+#             */
/*   Updated: 2022/01/30 21:06:49 by jibanez-         ###   ########.fr       */
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
	else if (line_read == NULL)
	{
		printf("quit\n");
		line_read = NULL;
	}
	return (line_read);
}
