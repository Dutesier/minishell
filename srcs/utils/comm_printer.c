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
	printf("%s", ft_color(YEL));
	printf("\nCOMMAND: %s\n", comm->cmd);
	while (comm->args && comm->args[i] != NULL)
	{
		printf("ARG[%i]: %s\n", i, comm->args[i]);
		i++;
	}
	printf("PIPING: %i\n", comm->piping);
	printf("IN: %s(%i)\nOUT: %s(%i)\n", comm->infile, comm->in, comm->outfile, comm->out);
	printf("%s\n", ft_color(WHT));
}
