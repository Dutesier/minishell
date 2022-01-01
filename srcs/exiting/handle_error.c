/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jibanez- <jibanez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/31 09:40:07 by jibanez-          #+#    #+#             */
/*   Updated: 2021/12/31 13:51:23 by jibanez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_error(t_shell *shell, int exit_code)
{
	(void)shell;
	// t_termcaps *termcaps;

	// termcaps = &shell->termcaps;
	exit(exit_code);
}