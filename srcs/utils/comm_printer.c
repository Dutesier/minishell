/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   comm_printer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dareias- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 16:43:39 by dareias-          #+#    #+#             */
/*   Updated: 2021/12/06 21:44:04 by dareias-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void comm_printer(t_comm *comm)
{
	int i;

	i = 0;
	printf("\nCOMMAND: %s\n", comm->cmd);
	while (comm->args && comm->args[i] != NULL)
	{
		printf("ARG[%i]: %s\n", i, comm->args[i]);
		i++;
	}
	printf("PIPING: %i\n\n", comm->piping);
}
