/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dareias- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 14:38:27 by dareias-          #+#    #+#             */
/*   Updated: 2022/02/06 01:06:25 by dareias-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_export(t_comm *ft_comm)
{
	char	*var;
	float	var_set;
	int		where;
	int		i;

	i = 1;
	if (!ft_comm->args[1])
		return (ft_print_export(ft_comm, 0));
	while (ft_comm->args[i])
	{
		var_set = var_is_set(ft_comm->shell, ft_comm->args[i]);
		where = (int)var_set;
		if (var_set - (float)where != 0.1)
		{
			var = whole_var_from_vars(ft_comm->shell->vars, ft_comm->args[i]);
			if (var)
			{
				ft_comm->shell->envp = add_envp(ft_comm->shell->envp, var);
				exports_log(ft_comm->shell, var);
			}
		}
		i++;
	}
//	return (ft_env(ft_comm, 1));
	return (0);
}

int ft_print_export(t_comm *ft_comm, int i)
{
	int sorted;
	int next;
	char **sorted_env;
	int env_ammount;

	while (ft_comm->shell->envp[i])
		i++;
	sorted_env = malloc(sizeof(char *) * (i + 1));
	if (!sorted_env)
		return (0);
	sorted_env[0] = NULL;

	sorted = 0;
	env_ammount = i;
	while (sorted < env_ammount)
	{
		next = get_next_lowest_env(sorted_env, ft_comm);
		sorted_env[sorted++] = ft_comm->shell->envp[next];
		sorted_env[sorted] = NULL;
	}
	print_sorted_env(sorted_env);
	free(sorted_env);
	return (sorted);
}

int env_in_sorted(char **sorted_env, char *env)
{
	int i;

	i = 0;
	while (sorted_env[i])
	{
		if (my_strcmp(sorted_env[i], env) == 0)
			return (1);
		i++;
	}
	return (0);
}

void print_sorted_env(char **sorted_env)
{
	int i;
	int j;

	i = 0;
	while (sorted_env[i])
	{
		printf("declare -x ");
		j = 0;
		while (sorted_env[i][j] != '=')
			printf("%c", sorted_env[i][j++]);
		printf("%c", sorted_env[i][j++]);
		printf("\"");
		while (sorted_env[i][j] != '\0')
			printf("%c", sorted_env[i][j++]);
		printf("\"\n");
		i++;
	}
}

int get_next_lowest_env(char **sorted_env, t_comm *ft_comm)
{
	int i;
	int ret;
	int cmp;
	int lowest;

	i = 0;
	lowest = 420;
	while (ft_comm->shell->envp[i])
	{	
		if (env_in_sorted(sorted_env, ft_comm->shell->envp[i]))
		{
			i++;
			continue ;
		}
		if (ft_comm->shell->envp[i][0] < lowest)
		{
			lowest = ft_comm->shell->envp[i][0];
			ret = i;
		}
		if (ft_comm->shell->envp[i][0] == lowest)
		{
			cmp = my_strcmp(ft_comm->shell->envp[i], ft_comm->shell->envp[ret]);
			if (cmp < 0)
				ret = i;
		}
		i++;
	}
	return (ret);
}
