/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   canonical.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jibanez- <jibanez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/29 18:02:08 by jibanez-          #+#    #+#             */
/*   Updated: 2022/01/01 17:20:13 by jibanez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef CANONICAL_H
#  define CANONICAL_H

# include "minishell.h"

void	handle_error(t_shell *shell, int exit_code);
void	init_termcaps(t_shell *shell);
char	*ft_find_value_from_key(const char *str, char *envp[]);
int 	capabilities(t_termcaps *termcaps);


# endif