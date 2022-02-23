/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jibanez- <jibanez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 17:25:18 by Jibanez-          #+#    #+#             */
/*   Updated: 2022/02/15 18:49:55 by jibanez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exit(t_comm *ft_comm)
{
	int	ex;

	ex = EXIT_SUCCESS;
	if (ft_comm->args[1])
		ex = ft_atoi(ft_comm->args[1]);
	if (ft_comm->shell->vars)
		clean_vars(ft_comm->shell);
	if (ft_comm->shell->envp)
		clean_envp(ft_comm->shell);
	/*if (ft_comm->shell->exports)
		clean_exports(ft_comm->shell);*/
	clean_shell(ft_comm->shell);
	if (ft_comm->shell->loop)
		clear_history();
	unlink(".mini.thd");
	if (ft_comm->shell->loop)
		write(1, "exit\n", 6);
	exit(ex);
}
