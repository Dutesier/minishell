/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_out.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dareias- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 16:39:01 by dareias-          #+#    #+#             */
/*   Updated: 2021/11/17 17:29:18 by dareias-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int change_out(int old_out_fd, char *new_out)
{
	int out;

	out = ft_getfd(new_out, 2);
	if (out == -1)
		return (print_error(FILE_OPEN_FAIL));
	dup2(out, old_out_fd);
	return (out);
}
