/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_line.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jibanez- <jibanez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 14:05:10 by dareias-          #+#    #+#             */
/*   Updated: 2022/01/31 13:04:35 by jibanez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_line(t_shell *shell)
{
	if (shell->line)
	{
		free(shell->line);
	}
	shell->line = readline(shell->prompt);
	if (shell->line && *shell->line)
		add_history(shell->line);
	else if (shell->line == NULL)
	{
		printf("quit\n");
		shell->loop = 0;
	}
}
