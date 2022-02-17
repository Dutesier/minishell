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

int set_pipes(t_comm *comm, int my_pipe[])
{
	if (comm->piping == 1) // our stdin should be the read end of the pipe
	{
		dup2(my_pipe[0], STDIN_FILENO);
		comm->in = my_pipe[0];
	}
	else if (comm->piping == 2)
	{
		DEBUG(fprintf(stderr, "My_pipe[1] before dup2 -> %i\n", my_pipe[1]));
		dup2(my_pipe[1], STDOUT_FILENO);
		DEBUG(fprintf(stderr, "My_pipe[1] after dup2 -> %i\n", my_pipe[1]));
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
