/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_fd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dareias- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 16:43:30 by dareias-          #+#    #+#             */
/*   Updated: 2022/03/05 13:24:29 by dareias-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_getfd(char *filename, int type)
{
	DEBUG(fprintf(stderr, "Returning fd for %s of type %i\n", filename, type));
	if (type == 2 || type == 4)
	{
		if (access(filename, F_OK))
		{
			ft_putstr_fd("minishell: ", STDERR_FILENO);
			ft_putstr_fd(filename, STDERR_FILENO);
			ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
			return (-1);
		}
		return (open(filename, O_RDONLY));
	}
	else if (type == 1)
		return (open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0644));
	else
		return (open(filename, O_APPEND | O_CREAT | O_WRONLY, 0644));
}
