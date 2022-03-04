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
	char	*h;
	int		reset_in;
	int		reset_out;

	DEBUG(fprintf(stderr, "Setting pipes: Piping (%i)\n", comm->piping));
	//save_std_io(comm->shell);
	//reset_std_io(comm->shell, 1, 1);
	reset_in = 1;
	reset_out = 1;
	if (comm->piping == 1 || comm->piping == 3)
	{
		save_std_io(comm->shell, 1, 0);
		reset_in = 0;
	}
	if (comm->piping == 2 || comm->piping == 3)
	{
		save_std_io(comm->shell, 0, 1);
		reset_out = 0;
	}
	if (comm->piping)
		if (set_pipes(comm))
			return (1);
	
	DEBUG(fprintf(stderr,"Set pipes\nHandling redirections (%i)\n", comm->redir));
	while (comm->redir > 0)
	{
		if (comm->redir % 10 == 2)
		{
			save_std_io(comm->shell, 1, 0);
			if (comm->shell->io.current_in != STDIN_FILENO)
				close(comm->shell->io.current_in);
			comm->shell->io.current_in = change_in(STDIN_FILENO, comm->infile, comm->redir % 10);
			reset_in = 0;
			if (comm->shell->io.current_in < 0)
				return (2);
		}
		else if (comm->redir % 10 == 1 || comm->redir % 10 == 3)
		{
			save_std_io(comm->shell, 0, 1);
			if (comm->shell->io.current_out != STDOUT_FILENO)
				close(comm->shell->io.current_out);
			comm->shell->io.current_out = change_out(STDOUT_FILENO, comm->outfile, comm->redir % 10);
			reset_out = 0;
			if (comm->shell->io.current_out < 0)
				return (3);
		}
		else if (comm->redir % 10 == 4)
		{
			save_std_io(comm->shell, 1, 0);
			reset_std_io(comm->shell, reset_in, reset_out);
			h = ft_heredoc(comm);
			if (comm->shell->io.current_in != STDIN_FILENO)
				close(comm->shell->io.current_in);
			comm->shell->io.current_in = change_in(STDIN_FILENO, h, comm->redir % 10);
			free(h);
			reset_in = 0;
			if (comm->shell->io.current_in < 0)
			{
				DEBUG(fprintf(stderr, "Error with heredoc\n"));
				return (4);
			}
			DEBUG(fprintf(stderr, "Done with heredoc\n"));
		}
		comm->redir = comm->redir / 10;
	}
	DEBUG(fprintf(stderr, "Reading from (%i) and writing to (%i)\n", comm->shell->io.current_in, comm->shell->io.current_out));
	reset_std_io(comm->shell, reset_in, reset_out);
	DEBUG(fprintf(stderr, "Reading from (%i) and writing to (%i)\n", comm->shell->io.current_in, comm->shell->io.current_out));
	return (0);
}

int reset_std_io(t_shell *shell, int reset_in, int reset_out)
{
	DEBUG(fprintf(stderr, "Resetting STD-IO: IN %s OUT %s\n", reset_in ? "true":"false", reset_out ? "true" : "false"));
	if (reset_in)
	{
		if (shell->io.saved_in)
		{
			DEBUG(fprintf(stderr, " - Resetting via dup2 STDIN_FILENO(%i)\n", STDIN_FILENO));
			dup2(shell->io.save_in, STDIN_FILENO);
			if (shell->io.current_in != STDIN_FILENO)
			{
				DEBUG(fprintf(stderr, " -- Closing shell->io.current_in: FD(%i)\n", shell->io.current_in));
				close(shell->io.current_in);
			}
			shell->io.current_in = shell->io.save_in;
			shell->io.saved_in = 0;
		}
	}
	if (reset_out)
	{
		if (shell->io.saved_out)
		{
			DEBUG(fprintf(stderr, " - Resetting via dup2 STDOUT_FILENO(%i)\n", STDOUT_FILENO));
			dup2(shell->io.save_out, STDOUT_FILENO);
			if (shell->io.current_out != STDOUT_FILENO)
			{
				DEBUG(fprintf(stderr, " -- Closing shell->io.current_out: FD(%i)\n", shell->io.current_out));
				close(shell->io.current_out);
			}
			shell->io.current_out = shell->io.save_out;
			shell->io.saved_out = 0;
		}
	}
	return (0);
}

void save_std_io(t_shell *shell, int in, int out)
{
	if (!shell->io.saved_in && in)
	{
		shell->io.save_in = dup(STDIN_FILENO);
		DEBUG(fprintf(stderr, "Saving (via dup) STDIN(%i)\n", shell->io.save_in));
		shell->io.saved_in = 1;
	}
	if (!shell->io.saved_out && out)
	{
		shell->io.save_out = dup(STDOUT_FILENO);
		DEBUG(fprintf(stderr, "Saving (via dup) STDOUT(%i)\n", shell->io.save_out));
		shell->io.saved_out = 1;
	}
}

void close_std_io_dups(t_shell *shell)
{
	if (shell->io.saved_in)
	{
		close(shell->io.save_in);
		DEBUG(fprintf(stderr, "Closing SavedIn: FD(%i)\n", shell->io.save_in));
		shell->io.saved_in = 0;
	}
	if (shell->io.saved_out)
	{
		close(shell->io.save_out);
		DEBUG(fprintf(stderr, "Closing SavedOut: FD(%i)\n", shell->io.save_out));
		shell->io.saved_out = 0;
	}
}
