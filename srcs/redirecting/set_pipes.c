/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_pipes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dareias- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 16:36:13 by dareias-          #+#    #+#             */
/*   Updated: 2022/02/14 20:00:12 by dareias-         ###   ########.fr       */
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

	printf("FDs: fd_p[0]: %i, fd_p[1]: %i, fd_n[0]: %i, fd_n[1]: %i\n", comm->fd_p[0],comm->fd_p[1],comm->fd_n[0],comm->fd_n[1]);
	if (comm->fd_p[1] > -1) // If the previous command was writing to us
		{fprintf(stderr, "Closing comm->fd_p[1]: (%i)\n",comm->fd_p[1]);close(comm->fd_p[1]);}
	if (comm->fd_n[0] > -1 && !comm->is_ft) // We wont read from the NEXT command
		{fprintf(stderr, "Closing comm->fd_n[0]: (%i)\n",comm->fd_n[0]);close(comm->fd_n[0]);} 
	if (comm->piping == 1)
	{
		dup2(comm->fd_p[0], STDIN_FILENO); // Means we're reading from the previous command
	}
	else if (comm->piping == 2) 
	{
		if (dup2(comm->fd_n[1], STDOUT_FILENO) == -1) // Means we're sending our output into the next commamnds input
			perror("piping 2 error");
	}
	else if (comm->piping == 3)
	{
		dup2(comm->fd_p[0], STDIN_FILENO); // Reading our INPUT from the PREVIOUS command
		dup2(comm->fd_n[1], STDOUT_FILENO); // Writing our OUTPUT to the NEXT command
	}
	if (comm->fd_p[0] > -1) // If the previous command was piping to us (we close it cause we already dupped it?)
		{fprintf(stderr, "Closing comm->fd_p[0]: (%i)\n",comm->fd_p[0]);close(comm->fd_p[0]);}
	if (comm->fd_n[1] > -1 && !comm->is_ft) // If we're piping to the next command (we close it cause we already dupped it?)
		{fprintf(stderr, "Closing comm->fd_n[1]: (%i)\n",comm->fd_n[1]);close(comm->fd_n[1]);}
	return (0);
}
