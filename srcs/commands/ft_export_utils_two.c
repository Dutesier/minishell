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
	
	DEBUG(fprintf(stderr, "SET NEW VAR\n");)

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
	char	*third_arg;
	int		save_idx;

	DEBUG(fprintf(stderr, "RESET VAR VARS\n");)
	save_idx = i;
	var = NULL;
	if (ft_comm->args[i + 1] && ft_comm->args[i + 1][0] == '='
		&& ft_comm->args[i + 1][1] == '\0') // Setting the var to a new value and exporting
	{
		var = ft_comm->args[i + 2];
		third_arg = var;
		if (!var)
			var = "";
		i += 2;
		if (third_arg)
			i++;
	}
	else
		i++;
	if (!var)
		ft_comm->shell->envp = add_envp(ft_comm->shell->envp, whole_var_from_vars(ft_comm->shell->vars, ft_comm->args[save_idx]));
	else
		update_var(ft_comm->shell, ft_comm->args[save_idx],
			var, var_set);
	return (i);
}

int	reset_var_envp(t_comm *ft_comm, int i, float var_set) // Var is set in envp
{
	char *var;
	char *third_arg;

	DEBUG(fprintf(stderr, "RESET VAR ENVP\n");)
	if (ft_comm->args[i + 1] && ft_comm->args[i + 1][0] == '='
		&& ft_comm->args[i + 1][1] == '\0')
	{
		var = ft_comm->args[i + 2];
		third_arg = var;
		if (!var)
			var = "";
		update_var(ft_comm->shell, ft_comm->args[i],
			var, var_set);
		//var = whole_var_from_vars(ft_comm->shell->vars, ft_comm->args[i]);
		//change_envp(ft_comm->shell->envp, where, ft_comm->args[i + 2]);
		i += 2;
		if (third_arg)
			i++;
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

