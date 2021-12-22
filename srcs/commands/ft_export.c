/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dareias- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 14:38:27 by dareias-          #+#    #+#             */
/*   Updated: 2021/12/22 14:53:48 by dareias-         ###   ########.fr       */
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
		return (ft_env(ft_comm, 1));
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

