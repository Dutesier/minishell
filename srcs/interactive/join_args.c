/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_args.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dareias- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/06 20:06:34 by dareias-          #+#    #+#             */
/*   Updated: 2022/02/08 19:34:12 by dareias-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *join_args(char **argv, int argc)
{
	int i;
	char *line;
	char *temp;
	
	i = 1;
	line = "";
	temp = NULL;
	while (i < argc)
	{
		temp = ft_strjoin(line, argv[i++]);
		if (i != 2)
			free(line);
		line = temp;
		temp = ft_strjoin(line, " ");
		if (i != 2)
			free(line);
		line = temp;
	}
	return (line);
}

