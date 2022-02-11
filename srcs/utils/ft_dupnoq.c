/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dupnoq.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dareias- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 19:32:45 by dareias-          #+#    #+#             */
/*   Updated: 2022/02/10 19:39:20 by dareias-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


char *ft_dupnoq(char *s)
{
	int i;
	int x;
	int inhib;
	char *sub;
	char *temp;

	i = 0;
	x = 0;
	if (!s)
		return (NULL);
	sub = malloc((ft_strlen(s) + 1) * sizeof(char));
	if (!sub)
		return (NULL);
	inhib = 0;
	while (s[x] != '\0')
	{
		if (s[x] == '\'')
		{
			if (!inhib)
			{
				inhib = 1;
				x++;
			}
			else if (inhib == 1)
			{
				inhib = 0;
				x++;
			}
			else
				sub[i++] = s[x++];
		}
		else if (s[x] == '\"')
		{
			if (!inhib)
			{
				inhib = 2;
				x++;
			}
			else if (inhib == 2)
			{
				inhib = 0;
				x++;
			}
			else
				sub[i++] = s[x++];
		}
		else
			sub[i++] = s[x++];
	}
	sub[i] = '\0';
	temp = malloc(sizeof(char) * (i + 1));
	if (!temp)
	{
		free(sub);
		return (NULL);
	}
	while (i >= 0)
	{
		temp[i] = sub[i];
		i--;
	}
	free(sub);
	free(s);
	return (temp);
}

