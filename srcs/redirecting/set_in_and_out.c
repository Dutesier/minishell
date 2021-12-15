/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_in_and_out.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dareias- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 15:57:45 by dareias-          #+#    #+#             */
/*   Updated: 2021/12/15 12:15:25 by dareias-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int set_in_and_out(t_comm *comm)
{
	if (comm->piping)
		if (set_pipes(comm))
			return (1);
	if (comm->redir == 2)
	{
		comm->in = change_in(STDIN_FILENO, comm->infile, comm->redir);
		if (!comm->in)
			return (1);
	}
	if (comm->redir == 1 || comm->redir == 3)
	{
		comm->out = change_out(STDOUT_FILENO, comm->outfile, comm->redir);
		if (!comm->out)
			return (1);
	}
	return (0);
}
