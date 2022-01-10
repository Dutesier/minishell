/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jibanez- <jibanez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 11:11:08 by dareias-          #+#    #+#             */
/*   Updated: 2021/12/29 19:47:26 by jibanez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

float var_is_set(t_shell *shell, char *var)
{
	// int i;
	int in_envp;
	int	in_vars;

	// i = 0;
	in_envp = var_in_envp(shell->envp, var);
	//printf("in_envp %i\n", in_envp);
	if (in_envp > -1)
		return ((float)in_envp + 0.1);
	if (!shell->vars)
		return (-1);
	in_vars = var_in_vars(shell->vars, var);
	if (in_vars > -1)
		return ((float)in_vars);
	return (-1);
}

int var_in_vars(char **vars, char *var)
{
	int i;
	int var_found;

	i = 0;
	var_found = 0;
	if (!vars || !vars[0])
		return (-1);
	//printf("vars[0] %s\n", vars[0]);
	while (vars[i] != NULL)
	{
		if (ft_strcmp_two(vars[i], var))
		{
			var_found = 1;
			break ;
		}
		i = i + 2;
	}
	if (var_found)
		return (i);
	return (-1);
}

int var_in_envp(char **envp, char *var)
{
	int		i;
	int		var_found;

	i = 0;
	var_found = 0;
	if (!envp || !envp[0])
		return (-1);
	//printf("var in envp %s\n", var);
	while (envp[i] != NULL)
	{
		if (ft_strcmp_envp(envp[i], var))
		{
			//printf("Found match: %s with %s\n", envp[i], var);
			var_found = 1;
			break ;
		}
		i++;
	}
	if (var_found)
		return (i);
	return (-1);
}

char *expansion_from_envp(t_shell *shell, int where)
{
	int i;
	int j;
	int m;
	char *expands;
	char *var;

	i = 0;
	j = 0;
	m = 0;
	var = shell->envp[where];
	while (var[i] != '=' && var[i] != '\0')
		i++;
	if (var[i++] == '\0')
		return (NULL);
	j = i;
	while (var[j] != '\0')
	{
		m++;
		j++;
	}
	expands = malloc(sizeof(char) * (m + 1));
	if (!expands)
		return (NULL);
	j = 0;
	while (var[i] != '\0')
	{
		expands[j++] = var[i++];
	}
	expands[j] = '\0';
	return (expands);
}
