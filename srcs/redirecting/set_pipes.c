/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_pipes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dareias- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 16:36:13 by dareias-          #+#    #+#             */
/*   Updated: 2021/11/17 17:01:24 by dareias-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 *
 * We read from pipe[0] and write to pipe[1]
 * 
*/

int set_pipes(t_comm *comm)
{
	close(comm->fd_p[1]);
	close(comm->fd_n[0]);
	if (comm->piping == 1)
	{
		dup2(comm->fd_p[0], STDIN_FILENO);
		close(comm->fd_n[1]);
	}
	if (comm->piping == 2)
	{
		close(comm->fd_p[0]);
		dup2(comm->fd_n[1], STDOUT_FILENO);
	}
	if (comm->piping == 3)
	{
		dup2(comm->fd_p[0], STDIN_FILENO);
		dup2(comm->fd_n[1], STDOUT_FILENO);
	}
	return (0);
}
