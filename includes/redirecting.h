/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirecting.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dareias- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 16:37:01 by dareias-          #+#    #+#             */
/*   Updated: 2021/12/15 12:11:29 by dareias-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIRECTING_H
# define REDIRECTING_H

int	ft_getfd(char *filename, int type);
int change_in(int old_in_fd, char *new_in, int redir);
int change_out(int old_out_fd, char *new_out, int redir);
int set_in_and_out(t_comm *comm);
int set_pipes(t_comm *comm);
int fd_closer(t_comm *comm);

#endif
