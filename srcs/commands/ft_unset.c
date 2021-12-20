/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dareias- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 18:58:00 by dareias-          #+#    #+#             */
/*   Updated: 2021/12/20 19:06:52 by dareias-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_unset(t_comm *ft_comm)
{
	int i;
	char *var;

	i = 1;
	if (!ft_comm->args[i])
		return (1);
	while (ft_comm->args[i])
	{
		var = whole_var(ft_comm, ft_comm->args[i]);
		if (var)
		{
			ft_comm->envp = rm_envp(ft_comm->envp, var);
			free(var);
		}
		i++;
	}
	return (i);
}
