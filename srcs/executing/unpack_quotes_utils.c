/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unpack_quotes_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dareias- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 17:35:39 by dareias-          #+#    #+#             */
/*   Updated: 2022/02/04 20:14:54 by dareias-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	dq_expanded_len(char *str)
{
	int	i;
	int	j;
	int	len;

	i = 0;
	len = 0;
	j = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '$')
			break ;
		i++;
	}
	len = i;
	while (str[i] != '\0' && str[i] != ' ')
		i++;
	while (str[i + j] != '\0')
		j++;
	len = len + j;
	return (len);
}

/*char	*exp_new_str(char *og_str, char *new_str, int i, int x)
{
	char	*variable_expanded;
	int		j;

	variable_expanded = getvar_from_dq(shell, og_str);
	if (!variable_expanded)
		variable_expanded = ft_strdup("");
	j = i;
	while (og_str[i] != '\0' && og_str[i] != ' ')
		i++;
	while (variable_expanded[x] != '\0')
		new_str[j++] = variable_expanded[x++];
	while (og_str[i] != '\0')
		new_str[j++] = og_str[i++];
	new_str[j] = '\0';
	free(variable_expanded);
	return (new_str);
}*/
