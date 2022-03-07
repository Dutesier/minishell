/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_in.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dareias- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 16:39:01 by dareias-          #+#    #+#             */
/*   Updated: 2022/03/05 12:51:36 by dareias-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	change_in(int old_in_fd, char *new_in, int redir)
{
	int	in;

	in = ft_getfd(new_in, redir);
	if (in == -1)
		return (print_error(FILE_OPEN_FAIL) - 2);
	else
		DEBUG(fprintf(stderr, "Got FD %s(%i)%s for %s%s%s\n", ft_color(YEL), in, ft_color(WHT),ft_color(YEL), new_in, ft_color(WHT)));
	dup2(in, old_in_fd);
	close(in);
	return (in);
}
