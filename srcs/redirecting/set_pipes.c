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
 * We read from comm->shell->io.my_pipe[0] and write to comm->shell->io.my_pipe[1]
 * if comm->is_ft then the fds we have are not duplicated
 * 
*/

int set_pipes(t_comm *comm)
{
	if (comm->piping == 1) // our stdin should be the read end of the pipe
	{
		if (comm->shell->io.current_in != STDIN_FILENO)
		{
			close(comm->shell->io.current_in);
			DEBUG(fprintf(stderr, "Closed (%i)\n", comm->shell->io.current_in));
		}
		if (dup2(comm->shell->io.my_pipe[0], STDIN_FILENO) < 0)
			return (print_error(IN_N_OUT_FAIL));
		comm->shell->io.current_in = comm->shell->io.my_pipe[0];
	}
	else if (comm->piping == 2)
	{
		if (comm->shell->io.current_out != STDOUT_FILENO)
		{
			close(comm->shell->io.current_out);
			DEBUG(fprintf(stderr, "Closed (%i)\n", comm->shell->io.current_out));
		}
		if (pipe(comm->shell->io.my_pipe) < 0)
			return (print_error(IN_N_OUT_FAIL));
		if (dup2(comm->shell->io.my_pipe[1], STDOUT_FILENO) < 0)
			return (print_error(IN_N_OUT_FAIL));
		comm->shell->io.current_out = comm->shell->io.my_pipe[1];
	}
	else if (comm->piping == 3)
	{
		if (comm->shell->io.current_in != STDIN_FILENO)
		{
			close(comm->shell->io.current_in);
			DEBUG(fprintf(stderr, "Closed (%i)\n", comm->shell->io.current_in));
		}
		if (comm->shell->io.current_out != STDOUT_FILENO)
		{
			close(comm->shell->io.current_out);
			DEBUG(fprintf(stderr, "Closed (%i)\n", comm->shell->io.current_out));
		}
		if (dup2(comm->shell->io.my_pipe[0], STDIN_FILENO) < 0)
			return (print_error(IN_N_OUT_FAIL) + fprintf(stderr, "comm->shell->io.my_pipe[0] = (%i)\n", comm->shell->io.my_pipe[0]));
		comm->shell->io.current_in = comm->shell->io.my_pipe[0];
		if (pipe(comm->shell->io.my_pipe) < 0)
			return (print_error(IN_N_OUT_FAIL));
		if (dup2(comm->shell->io.my_pipe[1], STDOUT_FILENO) < 0)
			return (print_error(IN_N_OUT_FAIL) + fprintf(stderr, "comm->shell->io.my_pipe[1] = (%i)\n", comm->shell->io.my_pipe[1]));
		comm->shell->io.current_out = comm->shell->io.my_pipe[1];
	}
	return (0);
}
