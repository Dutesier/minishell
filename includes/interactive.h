/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interactive.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dareias- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/06 20:19:29 by dareias-          #+#    #+#             */
/*   Updated: 2022/02/08 20:24:40 by dareias-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTERACTIVE_H
# define INTERACTIVE_H

char	*join_args(char **argv, int argc);
int		interactive_mode(t_shell *shell, char *argv[]);
char	*format_interactive_line(char *line);

#endif
