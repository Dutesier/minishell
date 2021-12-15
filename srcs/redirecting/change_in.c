/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_in.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dareias- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 16:39:01 by dareias-          #+#    #+#             */
/*   Updated: 2021/12/15 12:05:37 by dareias-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int change_in(int old_in_fd, char *new_in, int redir)
{
	int in;

	in = ft_getfd(new_in, redir);
	if (in == -1)
		return (print_error(FILE_OPEN_FAIL) - 1);
	dup2(in, old_in_fd);
	close(in);
	return (in);
}
