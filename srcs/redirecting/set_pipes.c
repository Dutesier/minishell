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
 * We read from my_pipe[0] and write to my_pipe[1]
 * if comm->is_ft then the fds we have are not duplicated
 * 
*/

/*
int set_pipes(t_comm *comm, int my_pipe[])
{

	printf("FDs: fd_p[0]: %i, fd_p[1]: %i, fd_n[0]: %i, fd_n[1]: %i\n", comm->fd_p[0],comm->fd_p[1],comm->fd_n[0],comm->fd_n[1]);

	if (comm->piping == 1)
	{
		if (!comm->is_ft)
			close(comm->fd_p[1]); // Meaning we are a fork and we have a filedes that is still open that we're not using
		dup2(comm->fd_p[0], STDIN_FILENO); // Means we're reading from the previous command
	}
	else if (comm->piping == 2)
	{
		if (!comm->is_ft) // We are a fork and we have no need of our open pipe to the previous process
		{
			close(comm->fd_p[0]);
			close(comm->fd_p[1]);
		}
		dup2(comm->fd_n[1], STDOUT_FILENO) // Means we're sending our output into the next commands input
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
*/

int set_pipes(t_comm *comm, int my_pipe[])
{
	if (comm->piping == 1) // our stdin should be the read end of the pipe
	{
		dup2(my_pipe[0], STDIN_FILENO);
		comm->in = my_pipe[0];
	}
	else if (comm->piping == 2)
	{
		fprintf(stderr, "My_pipe[1] before dup2 -> %i\n", my_pipe[1]);
		dup2(my_pipe[1], STDOUT_FILENO);
		fprintf(stderr, "My_pipe[1] after dup2 -> %i\n", my_pipe[1]);
		comm->out = my_pipe[1];
	}
	else if (comm->piping == 3)
	{
		dup2(my_pipe[0], STDIN_FILENO);
		dup2(my_pipe[1], STDOUT_FILENO);
		comm->in = my_pipe[0];
		comm->out = my_pipe[1];
	}
	return (0);
}
