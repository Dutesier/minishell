/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_in_and_out.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dareias- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 15:57:45 by dareias-          #+#    #+#             */
/*   Updated: 2021/11/17 17:36:50 by dareias-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int set_in_and_out(t_comm *comm)
{
	if (comm->piping)
		if (set_pipes(comm))
			return (1);
	if (comm->infile != NULL)
	{
		comm->in = change_in(STDIN_FILENO, comm->infile);
		if (comm->in)
			return (1);
	}
	if (comm->outfile != NULL)
	{
		comm->out = change_out(STDOUT_FILENO, comm->outfile);
		if (comm->out)
			return (1);
	}
	return (0);
}
