/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   comm_printer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dareias- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 16:43:39 by dareias-          #+#    #+#             */
/*   Updated: 2022/01/10 18:10:14 by dareias-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void comm_printer(t_comm *comm)
{
	int i;

	i = 0;
	fprintf(stderr,"%s", ft_color(YEL));
	fprintf(stderr,"\nCOMMAND: %s\n", comm->cmd);
	while (comm->args && comm->args[i] != NULL)
	{
		fprintf(stderr,"ARG[%i]: %s\n", i, comm->args[i]);
		i++;
	}
	fprintf(stderr,"PIPING: %i\n", comm->piping);
	fprintf(stderr,"IN: %s(%i)\nOUT: %s(%i)\n", comm->infile, comm->in, comm->outfile, comm->out);
	fprintf(stderr,"FD_P[0]: (%i)\nFD_P[1]: (%i)\n", comm->fd_p[0], comm->fd_p[1]);
	fprintf(stderr,"FD_N[0]: (%i)\nFD_N[1]: (%i)\n", comm->fd_n[0], comm->fd_n[1]);
	fprintf(stderr,"%s\n", ft_color(WHT));
}
