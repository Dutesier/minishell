/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_in_and_out.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dareias- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 15:57:45 by dareias-          #+#    #+#             */
/*   Updated: 2022/03/05 14:01:38 by dareias-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	set_in_and_out(t_comm *comm)
{
	int		reset_in;
	int		reset_out;

	DEBUG(fprintf(stderr, "Entered set_in_and_out:\n"));
	DEBUG(fprintf(stderr, "SaveIn (%s): %s%i%s\n", comm->shell->io.saved_in?"true":"false", ft_color(YEL), comm->shell->io.save_in, ft_color(WHT)));
	DEBUG(fprintf(stderr, "SaveOut (%s): %s%i%s\n", comm->shell->io.saved_out?"true":"false", ft_color(YEL), comm->shell->io.save_out, ft_color(WHT)));
	DEBUG(fprintf(stderr, "Current In: %s%i%s\n", ft_color(YEL), comm->shell->io.current_in, ft_color(WHT)));
	DEBUG(fprintf(stderr, "Current Out: %s%i%s\n", ft_color(YEL), comm->shell->io.current_out, ft_color(WHT)));
	DEBUG(fprintf(stderr, "Setting pipes: Piping (%i)\n", comm->piping));

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
	
	DEBUG(fprintf(stderr,"Set pipes\nHandling redirections (%i)\n", comm->redir.ammount));
	DEBUG(fprintf(stderr, "Writes: %s%i%s\n", ft_color(YEL), comm->redir.writes, ft_color(WHT)));
	DEBUG(fprintf(stderr, "Reads: %s%i%s\n", ft_color(YEL), comm->redir.reads, ft_color(WHT)));
	DEBUG(fprintf(stderr, "Appends: %s%i%s\n", ft_color(YEL), comm->redir.appends, ft_color(WHT)));
	DEBUG(fprintf(stderr, "Heredoc: %s%i%s\n", ft_color(YEL), comm->redir.heredoc, ft_color(WHT)));
	if (comm->redir.reads || comm->redir.heredoc)
		save_std_io(comm->shell, 1, 0);
	if (comm->redir.appends || comm->redir.writes)
		save_std_io(comm->shell, 0, 1);
	while (comm->redir.ammount > 0)
	{
		if (comm->redir.reads) // < 
		{
			if (comm->shell->io.current_in != STDIN_FILENO)
				close(comm->shell->io.current_in);
			comm->shell->io.current_in = change_in(STDIN_FILENO, comm->infile, comm->redir.reads);
			reset_in = 0;
			if (comm->shell->io.current_in < 0)
				return (2);
			comm->redir.reads = 0;
		}
		else if (comm->redir.writes) // >
		{
			if (comm->shell->io.current_out != STDOUT_FILENO)
				close(comm->shell->io.current_out);
			comm->shell->io.current_out = change_out(STDOUT_FILENO, comm->outfile, comm->redir.writes);
			reset_out = 0;
			if (comm->shell->io.current_out < 0)
				return (3);
			comm->redir.writes = 0;
		}
		else if (comm->redir.appends) //  >>
		{
			if (comm->shell->io.current_out != STDOUT_FILENO)
				close(comm->shell->io.current_out);
			comm->shell->io.current_out = change_out(STDOUT_FILENO, comm->outfile, comm->redir.appends);
			reset_out = 0;
			if (comm->shell->io.current_out < 0)
				return (3);
			comm->redir.appends = 0;
		}
		else if (comm->redir.heredoc) // HEREDOC ( << )
		{
			if (comm->shell->io.current_in != STDIN_FILENO)
				close(comm->shell->io.current_in);
			comm->shell->io.current_in = change_in(STDIN_FILENO, comm->heredoc_filename, comm->redir.heredoc);
			reset_in = 0;
			if (comm->shell->io.current_in < 0)
				return (4);
			DEBUG(fprintf(stderr, "Done with heredoc\n"));
		}
		comm->redir.ammount--;
	}
	DEBUG(fprintf(stderr, "Reading from (%i) and writing to (%i)\n", comm->shell->io.current_in, comm->shell->io.current_out));
	reset_std_io(comm->shell, reset_in, reset_out);
	DEBUG(fprintf(stderr, "Reading from (%i) and writing to (%i)\n", comm->shell->io.current_in, comm->shell->io.current_out));
	DEBUG(fprintf(stderr, "SaveIn (%s): %s%i%s\n", comm->shell->io.saved_in?"true":"false", ft_color(YEL), comm->shell->io.save_in, ft_color(WHT)));
	DEBUG(fprintf(stderr, "SaveOut (%s): %s%i%s\n", comm->shell->io.saved_out?"true":"false", ft_color(YEL), comm->shell->io.save_out, ft_color(WHT)));
	DEBUG(fprintf(stderr, "Current In: %s%i%s\n", ft_color(YEL), comm->shell->io.current_in, ft_color(WHT)));
	DEBUG(fprintf(stderr, "Current Out: %s%i%s\n", ft_color(YEL), comm->shell->io.current_out, ft_color(WHT)));

	return (0);
}

int	reset_std_io(t_shell *shell, int reset_in, int reset_out)
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

void	save_std_io(t_shell *shell, int in, int out)
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

void	close_std_io_dups(t_shell *shell)
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
