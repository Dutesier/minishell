/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interactive.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dareias- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/06 19:52:43 by dareias-          #+#    #+#             */
/*   Updated: 2022/02/06 20:29:57 by dareias-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int interactive_mode(t_shell *shell, char *argv[], int argc)
{
	shell->line = join_args(argv, argc); 
	if (shell->line != NULL)
	{
		parse_line(shell);
		clean_shell(shell);
	}
	if (shell->vars)
		clean_vars(shell);
	if (shell->exports)
		clean_exports(shell);
	return (EXIT_SUCCESS);
}
