/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_in.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dareias- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 16:39:01 by dareias-          #+#    #+#             */
/*   Updated: 2021/11/17 17:29:09 by dareias-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int change_in(int old_in_fd, char *new_in)
{
	int in;

	in = ft_getfd(new_in, 1);
	if (in == -1)
		return (print_error(FILE_OPEN_FAIL));
	dup2(in, old_in_fd);
	return (in);
}
