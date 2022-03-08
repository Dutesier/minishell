/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils_two.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dareias- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 22:30:43 by dareias-          #+#    #+#             */
/*   Updated: 2022/03/07 22:30:45 by dareias-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	set_new_var(t_comm *ft_comm, int i, int save)
{
	char	*var;

	if (!ft_comm->args[i + 1])
		add_variable(ft_comm->shell, ft_comm->args[i++], NULL);
	else if (ft_comm->args[i + 1][0] == '='
		&& ft_comm->args[i + 1][1] == '\0')
	{
		if (!ft_comm->args[i + 2])
		{
			add_variable(ft_comm->shell, ft_comm->args[i], "");
			i += 2;
		}
		else
		{	
			add_variable(ft_comm->shell, ft_comm->args[i],
				ft_comm->args[i + 2]);
			i += 3;
		}
	}
	else
		add_variable(ft_comm->shell, ft_comm->args[i++], NULL);
	var = whole_var_from_vars(ft_comm->shell->vars, ft_comm->args[save]);
	if (var)
		ft_comm->shell->envp = add_envp(ft_comm->shell->envp, var);
	return (i);
}

int	reset_var_vars(t_comm *ft_comm, int i, float var_set)
{
	char	*var;

	if (ft_comm->args[i + 1] && ft_comm->args[i + 1][0] == '='
		&& ft_comm->args[i + 1][1] == '\0')
	{
		update_var(ft_comm->shell, ft_comm->args[i],
			ft_comm->args[i + 2], var_set);
		var = whole_var_from_vars(ft_comm->shell->vars, ft_comm->args[i]);
		i += 3;
	}
	else
		var = whole_var_from_vars(ft_comm->shell->vars, ft_comm->args[i++]);
	if (var)
		ft_comm->shell->envp = add_envp(ft_comm->shell->envp, var);
	return (i);
}

int	reset_var_envp(t_comm *ft_comm, int i, int where)
{
	if (ft_comm->args[i + 1] && ft_comm->args[i + 1][0] == '='
		&& ft_comm->args[i + 1][1] == '\0')
	{
		change_envp(ft_comm->shell->envp, where, ft_comm->args[i + 2]);
		i += 3;
	}
	else
		i++;
	return (i);
}

int	is_it_lowest(char **sorted_env, char **unsorted, int i)
{
	int	lowest;
	int	j;

	lowest = 1;
	j = 0;
	while (unsorted[j])
	{
		if (i == j || env_in_sorted(sorted_env, unsorted[j]))
		{
			j++;
			continue ;
		}
		if (my_strcmp(unsorted[i], unsorted[j]) > 0)
		{
			lowest = 0;
			break ;
		}
		j++;
	}
	return (lowest);
}
