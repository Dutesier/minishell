/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   canonical_mode.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jibanez- <jibanez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/29 18:01:00 by jibanez-          #+#    #+#             */
/*   Updated: 2021/12/29 19:55:03 by jibanez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "canonical.h"

void	init_termcaps(t_shell *shell)
{
	char	*term_type;

	if (tcgetattr(STDIN_FILENO, &shell->termcaps.old_term) == -1)
		handle_error(shell, EXIT_FAILURE);
	term_type = ft_getenv("TERM");
	if (!term_type)
		handle_error(shell, EXIT_FAILURE);
	if (tgetent(shell->termcaps.buffer, term_type) <= 0)
		handle_error(shell, EXIT_FAILURE);
	else if (!has_capabilities(shell->termcaps))
		handle_error(shell, EXIT_FAILURE);
	free(term_type);
}

void	canonical_on()
{

}

void	canonical_off()
{

}

void	handle_error(t_shell *shell, int exit_code)
{
	t_termcaps *termcaps;

	termcaps = &shell->termcaps;
	exit(exit_code);
}