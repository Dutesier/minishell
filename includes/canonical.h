/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   canonical.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jibanez- <jibanez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/29 18:02:08 by jibanez-          #+#    #+#             */
/*   Updated: 2022/02/10 21:22:56 by dareias-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CANONICAL_H
# define CANONICAL_H

# include "minishell.h"

void	canonical_on(t_shell *shell);
void	canonical_off(t_shell *shell);
void	handle_error(t_shell *shell, int exit_code);
void	init_termcaps(t_shell *shell);
char	*ft_find_value_from_key(char *str, char *envp[]);
int		capabilities(t_termcaps *termcaps);
void	termcaps_to_null(t_termcaps *termcaps);

#endif