/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_out.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dareias- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 16:39:01 by dareias-          #+#    #+#             */
/*   Updated: 2022/03/05 12:51:30 by dareias-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	change_out(int old_out_fd, char *new_out, int redir)
{
	int	out;

	out = ft_getfd(new_out, redir);
	if (out == -1)
		return (print_error(FILE_OPEN_FAIL) - 2);
	DEBUG(fprintf(stderr, "Got FD %s(%i)%s for %s%s%s\n", ft_color(YEL), out, ft_color(WHT),ft_color(YEL), new_out, ft_color(WHT)));
	dup2(out, old_out_fd);
	return (out);
}
