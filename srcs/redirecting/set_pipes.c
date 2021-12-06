/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_pipes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dareias- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 16:36:13 by dareias-          #+#    #+#             */
/*   Updated: 2021/12/06 21:43:24 by dareias-         ###   ########.fr       */
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

	//printf("FDs: fd_p[0]: %i, fd_p[1]: %i, fd_n[0]: %i, fd_n[1]: %i\n", comm->fd_p[0],comm->fd_p[1],comm->fd_n[0],comm->fd_n[1]);
	if (comm->fd_p[1] > -1)
		close(comm->fd_p[1]);
	if (comm->fd_n[0] > -1)
		close(comm->fd_n[0]);
	if (comm->piping == 1)
	{
		dup2(comm->fd_p[0], STDIN_FILENO);
	}
	if (comm->piping == 2)
	{
		dup2(comm->fd_n[1], STDOUT_FILENO);
	}
	if (comm->piping == 3)
	{
		dup2(comm->fd_p[0], STDIN_FILENO);
		dup2(comm->fd_n[1], STDOUT_FILENO);
	}
	if (comm->fd_p[0] > -1)
		close(comm->fd_p[0]);
	if (comm->fd_n[1] > -1)
		close(comm->fd_n[1]);
	return (0);
}
