/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_in_and_out.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dareias- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 15:57:45 by dareias-          #+#    #+#             */
/*   Updated: 2022/02/14 19:33:22 by dareias-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int set_in_and_out(t_comm *comm)
{
	char *h;

	reset_std_io(comm, 1, 1);
	if (comm->piping)
		if (set_pipes(comm, comm->my_pipe))
			return (1);
	fprintf(stderr,"Set pipes\nHandling redirections (%i)\n", comm->redir);
	while (comm->redir > 0)
	{
		if (comm->redir % 10 == 2)
		{
			comm->in = change_in(comm->in, comm->infile, comm->redir % 10);
			if (comm->in < 0)
				return (1);
		}
		else if (comm->redir % 10 == 1 || comm->redir % 10 == 3)
		{
			comm->out = change_out(comm->out, comm->outfile, comm->redir % 10);
			if (comm->out < 0)
				return (1);
		}
		else if (comm->redir % 10 == 4)
		{
			h = ft_heredoc(comm);
			comm->in = change_in(comm->in, h, comm->redir % 10);
			free(h);
			if (comm->in < 0)
				return (1);
		}
		comm->redir = comm->redir / 10;
	}
	fprintf(stderr, "Reading from (%i) and writing to (%i)\n", comm->in, comm->out);
	return (0);
}

int reset_std_io(t_comm *comm, int reset_in, int reset_out)
{
	fprintf(stderr, "Resetting std io\n");
	if (reset_in)
	{
		if (comm->in != STDIN_FILENO)
		{
			fprintf(stderr, "Dupping COMM->IN(%i) to STDIN_FILENO(%i)\n", comm->in, STDIN_FILENO);
			dup2(comm->shell->save_in, STDIN_FILENO);
			fprintf(stderr, "Closing current in: FD(%i)\n", comm->in);
			close(comm->in);
		}
		comm->in = STDIN_FILENO;
	}
	if (reset_out)
	{
		if (comm->out != STDOUT_FILENO)
		{
			fprintf(stderr, "Dupping COMM->OUT(%i) to STDOUT_FILENO(%i)\n", comm->out, STDOUT_FILENO);
			dup2(comm->shell->save_out, STDOUT_FILENO);
			fprintf(stderr, "Closing current out: FD(%i)\n", comm->out);
			close(comm->out);
		}
		comm->out = STDOUT_FILENO;
	}
	return (0);
}
