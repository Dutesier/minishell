/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dareias- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 14:38:27 by dareias-          #+#    #+#             */
/*   Updated: 2021/12/20 19:30:10 by dareias-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_export(t_comm *ft_comm)
{
	char	*var;
	int		i;

	i = 1;
	if (!ft_comm->args[1])
		return (ft_env(ft_comm, 1));
	while (ft_comm->args[i])
	{
		var = whole_var(ft_comm, ft_comm->args[i]);
		if (var)
			ft_comm->envp = add_envp(ft_comm->envp, var);
		i++;
	}
//	return (ft_env(ft_comm, 1));
	return (0);
}

