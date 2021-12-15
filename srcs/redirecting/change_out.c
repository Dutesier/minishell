/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_out.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dareias- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 16:39:01 by dareias-          #+#    #+#             */
/*   Updated: 2021/12/15 12:20:13 by dareias-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int change_out(int old_out_fd, char *new_out, int redir)
{
	int out;

	out = ft_getfd(new_out, redir);
	if (out == -1)
		return (print_error(FILE_OPEN_FAIL) - 1);
//	printf("FD %i now points to %s(%i)\n", old_out_fd, new_out, out); 
	dup2(out, old_out_fd);
	close(out);
	return (out);
}
