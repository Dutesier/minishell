/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jibanez- < jibanez-@student.42lisboa.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 17:25:18 by Jibanez-          #+#    #+#             */
/*   Updated: 2021/12/30 14:59:42 by dareias-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exit(t_comm *ft_comm)
{
	int ex;

	ex = EXIT_SUCCESS;
	if (ft_comm->args[1])
		ex = ft_atoi(ft_comm->args[1]);
	if (ft_comm->shell->vars)
		clean_vars(ft_comm->shell);
	if (ft_comm->shell->exports)
		clean_exports(ft_comm->shell);
	clean_shell(ft_comm->shell);
	clear_history();	
	unlink(".mini.thd");
    write(1, "exit\n", 6);
    exit(ex);
}
