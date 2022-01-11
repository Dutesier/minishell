/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dupnoq.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dareias- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 19:32:45 by dareias-          #+#    #+#             */
/*   Updated: 2022/01/11 20:07:49 by dareias-         ###   ########.fr       */
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
	temp = s;
	sub = malloc((ft_strlen(s) + 1) * sizeof(char));
	if (!sub)
		return (NULL);
	inhib = 0;
	while (s[x] != '\0')
	{
		if (s[x] == '\'')
		{
			if (inhib == 1)
				inhib = 0;
			else if (inhib == 0)
				inhib = 1;
		}
		if (s[x] == '\"')
		{
			if (inhib == 2)
				inhib = 0;
			else if (inhib == 0)
				inhib = 2;
		}
		if (inhib == 1)
		{
			if (s[x] == '\'')
				x++;
			else
				sub[i++] = s[x++];	
		}
		else if (inhib == 2)
		{
			if (s[x] == '\"')
				x++;
			else
				sub[i++] = s[x++];
		}
		else
			sub[i++] = s[x++];
	}
	sub[i] = '\0';
	free(temp);
	temp = malloc(sizeof(char) * i);
	while (i >= 0)
	{
		temp[i] = sub[i];
		i--;
	}
	free(sub);
	return (temp);
}

