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

static void	print_env(char **env);

int	ft_env(t_comm *ft_comm)
{
	int	i;

	i = 0;
	if (!ft_comm->shell->envp)
		return (1);
	print_env(ft_comm->shell->envp);
	return (0);
}

static void	print_env(char **env)
{
	int	i;
	int	j;

	i = 0;
	while (env[i])
	{
		j = 0;
		while (env[i][j] != '=')
			printf("%c", env[i][j++]);
		printf("%c", env[i][j++]);
		while (env[i][j] != '\0')
			printf("%c", env[i][j++]);
		printf("\n");
		i++;
	}
}
