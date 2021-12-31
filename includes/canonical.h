/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   canonical.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jibanez- <jibanez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/29 18:02:08 by jibanez-          #+#    #+#             */
/*   Updated: 2021/12/31 09:44:09 by jibanez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef CANONICAL_H
#  define CANONICAL_H

# include "minishell.h"

void	handle_error(t_shell *shell, int exit_code);
void	init_termcaps(t_shell *shell);
char	*ft_getenv(const char *str, char *envp[]);


# endif