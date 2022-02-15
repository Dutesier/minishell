/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jibanez- <jibanez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 18:58:00 by dareias-          #+#    #+#             */
/*   Updated: 2022/02/15 18:44:22 by jibanez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_unset(t_comm *ft_comm)
{
	float	var_set;
	int		where;
	int		i;
	char	*var;

	i = 1;
	if (!ft_comm->args[i])
		return (1);
	while (ft_comm->args[i++])
	{
		var_set = var_is_set(ft_comm->shell, ft_comm->args[i]);
		where = (int)var_set;
		if (var_set > -1 && var_set - (float)where == 0)
		{
			var = whole_var_from_vars(ft_comm->shell->vars, ft_comm->args[i]);
			rm_var_from_vars(ft_comm->shell, ft_comm->args[i]);
			free(var);
		}
		else if (var_set > -1)
		{
			ft_comm->shell->envp = rm_envp(ft_comm->shell->envp, ft_comm->shell->envp[where], ft_comm->shell->exports);
			rm_var_from_vars(ft_comm->shell, ft_comm->args[i]);
		}
	}
	return (i);
}
