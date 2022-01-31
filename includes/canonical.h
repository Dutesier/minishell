/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   canonical.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jibanez- <jibanez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/29 18:02:08 by jibanez-          #+#    #+#             */
/*   Updated: 2022/01/29 22:35:48 by jibanez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef CANONICAL_H
#  define CANONICAL_H

# include "minishell.h"

void	canonical_on(t_shell *shell);
void	canonical_off(t_shell *shell);
void	handle_error(t_shell *shell, int exit_code);
void	init_termcaps(t_shell *shell);
char	*ft_find_value_from_key(const char *str, char *envp[]);
int 	capabilities(t_termcaps *termcaps);
void	termcaps_to_null(t_termcaps *termcaps);


# endif