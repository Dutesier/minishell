/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dareias- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 15:44:39 by dareias-          #+#    #+#             */
/*   Updated: 2021/11/17 17:28:38 by dareias-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int run_command(t_comm *comm)
{
	pid_t	pid;
	int		sta;
	int		error;
	

	pid = fork();
	if (pid == -1)
		return (print_error(FORK_FAIL));
	if (pid == 0)
	{
		if (set_in_and_out(comm))
			return (1);

		error = execve(comm->cmd, comm->args, NULL);
		if (error < 0)
			return (print_error(EXEC_FAIL));
	}
	else
	{
		waitpid(pid, &sta, 0);
		sta = WEXITSTATUS(sta);
		if (sta)
			return (1);
		return (0);
	}
	return (0);
}
