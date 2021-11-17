/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_closer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dareias- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 17:02:26 by dareias-          #+#    #+#             */
/*   Updated: 2021/11/17 17:30:23 by dareias-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int close_pipes(t_comm *comm)
{
	if (comm->piping == 1)
		close(comm->fd_p[0]);
	if (comm->piping == 2)
		close(comm->fd_n[1]);
	if (comm->piping == 3)
	{
		close(comm->fd_p[0]);
		close(comm->fd_n[1]);
	}
	return (0);
}

static int close_fds(t_comm *comm)
{
	if (comm->in)
		close(comm->in);
	if (comm->out)
		close(comm->out);
	return (0);
}

int fd_closer(t_comm *comm)
{
	if (comm->piping)
		if (close_pipes(comm))
			return (1);
	if (close_fds(comm))
		return (1);
	return (0);
}
