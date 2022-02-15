/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_envp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jibanez- <jibanez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 18:16:14 by dareias-          #+#    #+#             */
/*   Updated: 2022/02/15 18:51:43 by jibanez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**add_envp(char **envp, char *add)
{
	int		i;
	char	**new;

	i = 0;
	while (envp[i])
		i++;
	new = malloc(sizeof(char *) * (i + 2));
	if (!new)
		return (NULL);
	i = 0;
	while (envp[i++])
		new[i] = envp[i];
	new[i++] = add;
	return (new);
}

char	**rm_envp(char **envp, char *rm, char **exports)
{
	int		i;
	int		j;
	int		l;
	char	**new;

	i = 0;
	j = 0;
	l = 0;
	if (!envp || !envp[j])
		return (NULL);
	while (envp[j])
		j++;
	new = malloc(sizeof(char *) * (j));
	if (!new)
		return (NULL);
	while (envp[i])
	{
		if (ft_strcmp_two(rm, envp[i]))
		{
			if (did_i_export(rm, exports))
				free(envp[i]);
			i++;
		}
		if (envp[i] == NULL)
			break ;
		new[l] = envp[i];
		i++;
		l++;
	}
	new[l] = NULL;
	if (i == l)
	{
		free(new);
		return (envp);
	}
	return (new);
}

char	*whole_var_from_vars(char **vars, char *var)
{
	int		i;
	char	*temp;
	char	*final;

	i = 0;
	if (!vars || !vars[0])
		return (NULL);
	while (vars[i])
	{
		if (ft_strcmp_two(vars[i], var))
			break ;
		i = i + 2;
	}
	if (!vars[i])
		return (NULL);
	temp = ft_strcat(vars[i], "=");
	final = ft_strcat(temp, vars[i + 1]);
	free(temp);
	return (final);
}

void	rm_var_from_vars(t_shell *shell, char *var)
{
	int		i;
	int		size;
	int		var_set;
	char	**temp;

	i = 0;
	size = 0;
	var_set = 0;
	if (!shell->vars || !shell->vars[i])
		return ;
	while (shell->vars[size] != NULL)
		size++;
	if (size == 0)
		return ;
	while (shell->vars[i] != NULL)
	{
		if (ft_strcmp_two(shell->vars[i], var))
			var_set = 1;
		i++;
	}
	if (!var_set)
	{
		return ;
	}
	temp = malloc(sizeof(char *) * (size - 1));
	if (!temp)
		return ;
	i = 0;
	size = 0;
	while (shell->vars[i] != NULL)
	{
		if (ft_strcmp_two(shell->vars[i], var))
		{
			free(shell->vars[i++]);
			free(shell->vars[i++]);
		}
		if (shell->vars[i])
			temp[size++] = shell->vars[i++];
	}
	temp[size] = NULL;
	if (shell->vars)
		free(shell->vars);
	shell->vars = temp;
	return ;
}

int	did_i_export(char *var, char **exports)
{
	int	i;

	i = 0;
	while (exports && exports[i] != NULL)
	{
		if (ft_strcmp_two(var, exports[i]))
			return (1);
		i++;
	}
	return (0);
}
