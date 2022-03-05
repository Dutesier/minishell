/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dareias- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 17:17:56 by Jibanez-          #+#    #+#             */
/*   Updated: 2022/03/05 19:10:11 by dareias-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_sorted_env(char **sorted_env);
static int	ft_print_env(t_comm *ft_comm, int i);

int	ft_env(t_comm *ft_comm)
{
	int	i;

	i = 0;
	if (!ft_comm->shell->envp)
		return (1);
	ft_print_env(ft_comm, 0);
	return (0);
}

static int	ft_print_env(t_comm *ft_comm, int i)
{
	int		sorted;
	int		next;
	char	**sorted_env;
	int		env_ammount;

	while (ft_comm->shell->envp[i])
		i++;
	sorted_env = malloc(sizeof(char *) * (i + 1));
	if (!sorted_env)
		return (print_error(MEMORY_FAIL));
	sorted_env[0] = NULL;
	sorted = 0;
	env_ammount = i;
	while (sorted < env_ammount)
	{
		next = get_next_lowest_env(sorted_env, ft_comm->shell->envp);
		sorted_env[sorted++] = ft_comm->shell->envp[next];
		sorted_env[sorted] = NULL;
	}
	print_sorted_env(sorted_env);
	free(sorted_env);
	return (0);
}

static void	print_sorted_env(char **sorted_env)
{
	int	i;
	int	j;

	i = 0;
	while (sorted_env[i])
	{
		j = 0;
		while (sorted_env[i][j] != '=')
			printf("%c", sorted_env[i][j++]);
		printf("%c", sorted_env[i][j++]);
		while (sorted_env[i][j] != '\0')
			printf("%c", sorted_env[i][j++]);
		printf("\n");
		i++;
	}
}