/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dareias- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 14:38:27 by dareias-          #+#    #+#             */
/*   Updated: 2022/03/05 19:58:43 by dareias-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_sorted_export(char **sorted_env);

int	ft_export(t_comm *ft_comm)
{
	char	*var;
	float	var_set;
	int		where;
	int		i;
	int		save;

	i = 1;
	if (!ft_comm->args[1])
		return (ft_print_export(ft_comm));
	while (ft_comm->args[i])
	{
		var_set = var_is_set(ft_comm->shell, ft_comm->args[i]);
		where = (int)var_set;
		save = i;
		if (var_set == -1.0) // var isnt set in envp or our vars
		{
			if (!ft_comm->args[i + 1])
			{
				add_variable(ft_comm->shell,ft_comm->args[i], NULL);
				i++;
				//fprintf(stderr, "Export: 1\n");
			}
			else if (ft_comm->args[i+1][0] == '=' && ft_comm->args[i+1][1] == '\0')
			{
				if (!ft_comm->args[i + 2])
				{
					add_variable(ft_comm->shell,ft_comm->args[i], "");
					i +=2;
				}
				else
				{	
					add_variable(ft_comm->shell,ft_comm->args[i],ft_comm->args[i + 2]);
					i +=3;
				}
				//fprintf(stderr, "Export: 2\n");
			}
			else
			{
				add_variable(ft_comm->shell,ft_comm->args[i], NULL);
				i++;
				//fprintf(stderr, "Export: 3\n");
			}
			var = whole_var_from_vars(ft_comm->shell->vars, ft_comm->args[save]);
			if (var)
			{
				//fprintf(stderr, "Export: Adding to envp\n");
				ft_comm->shell->envp = add_envp(ft_comm->shell->envp, var);

				if (!ft_comm->shell->envp)
					fprintf(stderr, "Envp = null\n");
			}
		}
		else if (var_set - (float)where != 0.1) // Var is set in our vars
		{
			if (ft_comm->args[i+1] && ft_comm->args[i+1][0] == '=' && ft_comm->args[i+1][1] == '\0')
			{
				update_var(ft_comm->shell, ft_comm->args[i], ft_comm->args[i+2], var_set);
				var = whole_var_from_vars(ft_comm->shell->vars, ft_comm->args[i]);
				i += 3;
				//fprintf(stderr, "Export: 4\n");
			}
			else
				var = whole_var_from_vars(ft_comm->shell->vars, ft_comm->args[i++]);
			if (var)
			{
				ft_comm->shell->envp = add_envp(ft_comm->shell->envp, var);
				//fprintf(stderr, "Export: 5\n");
				if (!ft_comm->shell->envp)
					fprintf(stderr, "Envp = null\n");
			}
		}
		else // we need to update the var in shell envp
		{
			if (ft_comm->args[i+1] && ft_comm->args[i+1][0] == '=' && ft_comm->args[i+1][1] == '\0')
			{
				change_envp(ft_comm->shell->envp, where,ft_comm->args[i + 2]);
				i += 3;
				//fprintf(stderr, "Export: 6\n");
			}
			else
				i++;
		}
	}
	return (0);
}
/*	return (ft_env(ft_comm, 1)); */

int	ft_print_export(t_comm *ft_comm)
{
	int		sorted;
	int		next;
	char	**sorted_env;
	int		env_ammount;

	env_ammount = build_unsorted_env(ft_comm);
	sorted_env = malloc(sizeof(char *) * (env_ammount + 1));
	if (!sorted_env)
		return (print_error(MEMORY_FAIL));
	sorted_env[0] = NULL;
	sorted = 0;
	while (sorted < env_ammount)
	{
		next = get_next_lowest_env(sorted_env, ft_comm->unsorted_env);
		sorted_env[sorted++] = ft_comm->unsorted_env[next];
		sorted_env[sorted] = NULL;
	}
	print_sorted_export(sorted_env);
	free(sorted_env);
	free(ft_comm->unsorted_env);
	return (0);
}

int	env_in_sorted(char **sorted_env, char *env)
{
	int	i;

	i = 0;
	while (sorted_env[i])
	{
		if (my_strcmp(sorted_env[i], env) == 0)
			return (1);
		i++;
	}
	return (0);
}

static void	print_sorted_export(char **sorted_env)
{
	int	i;
	int	j;

	i = 0;
	while (sorted_env[i])
	{
		printf("declare -x ");
		j = 0;
		while (sorted_env[i][j] != '=' && sorted_env[i][j] != '\0')
			printf("%c", sorted_env[i][j++]);
		if (sorted_env[i][j] == '\0')
		{
			i++;
			printf("\n");
			continue ;
		}
		printf("%c", sorted_env[i][j++]);
		printf("\"");
		while (sorted_env[i][j] != '\0')
			printf("%c", sorted_env[i][j++]);
		printf("\"\n");
		i++;
	}
}

int	get_next_lowest_env(char **sorted_env, char **unsorted)
{
	int	i;
	int j;
	int	lowest;

	i = 0;
	while (unsorted[i])
	{
		if (env_in_sorted(sorted_env, unsorted[i]))
		{
			i++;
			continue ;
		}
		j = 0;
		lowest = 1;
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
		if (lowest)
		{
			return (i);
		}
		else
			i++;
	}
	return (-1);
}
