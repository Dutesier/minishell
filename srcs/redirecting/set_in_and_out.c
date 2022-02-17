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

static void save_std_io(t_comm *comm);

int set_in_and_out(t_comm *comm)
{
	char *h;

	save_std_io(comm);
	reset_std_io(comm, 1, 1);
	if (comm->piping)
		if (set_pipes(comm, comm->my_pipe))
			return (1);
	DEBUG(fprintf(stderr,"Set pipes\nHandling redirections (%i)\n", comm->redir));
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
	DEBUG(fprintf(stderr, "Reading from (%i) and writing to (%i)\n", comm->in, comm->out));
	return (0);
}

int reset_std_io(t_comm *comm, int reset_in, int reset_out)
{
	DEBUG(fprintf(stderr, "Resetting std io\n"));
	if (reset_in)
	{
		if (comm->in != STDIN_FILENO)
		{
			DEBUG(fprintf(stderr, "Resetting via dup2 STDIN_FILENO(%i)\n", STDIN_FILENO));
			dup2(comm->shell->save_in, STDIN_FILENO);
			DEBUG(fprintf(stderr, "Closing Comm->in: FD(%i)\n", comm->in));
			close(comm->in);
		}
		comm->in = STDIN_FILENO;
	}
	if (reset_out)
	{
		if (comm->out != STDOUT_FILENO)
		{
			DEBUG(fprintf(stderr, "Closing comm->out: FD(%i)\n", comm->out));
			close(comm->out);
			DEBUG(fprintf(stderr, "Resetting via dup2 STDOUT_FILENO(%i)\n", STDOUT_FILENO));
			dup2(comm->shell->save_out, STDOUT_FILENO);
		}
		comm->out = STDOUT_FILENO;
	}
	return (0);
}

static void save_std_io(t_comm *comm)
{
	if (!comm->shell->saved)
	{
		comm->shell->save_in = dup(STDIN_FILENO);
		comm->shell->save_out = dup(STDOUT_FILENO);
		DEBUG(fprintf(stderr, "Saving (via dup) STDIN(%i) and STDOUT(%i)\n", comm->shell->save_in, comm->shell->save_out));
		comm->shell->saved = 1;
	}
}

void close_std_io_dups(t_shell *shell)
{
	if (shell->saved)
	{
		close(shell->save_out);
		DEBUG(fprintf(stderr, "Closing SavedOut: FD(%i)\n", shell->save_out));
		close(shell->save_in);
		DEBUG(fprintf(stderr, "Closing SavedIn: FD(%i)\n", shell->save_in));
		shell->saved = 0;
	}
}
