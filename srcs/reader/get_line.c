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

static void add_exit_val_prompt(t_shell *shell);
static void add_cwd_prompt(t_shell *shell);

void	get_line(t_shell *shell)
{
	if (shell->line)
	{
		free(shell->line);
	}
	add_exit_val_prompt(shell);
	get_cwd(shell);
	shell->line = readline(shell->prompt);
	if (shell->line && *shell->line)
		add_history(shell->line);
	else if (shell->line == NULL)
	{
		printf("quit\n");
		shell->loop = 0;
	}
}

static void add_exit_val_prompt(t_shell *shell)
{
	char	*new_prompt;
	char	*exit_val;
	char	*exit_stat;

	add_cwd_prompt(shell);
	exit_stat = ft_itoa(shell->last_exit);
	exit_val = ft_strjoin(exit_stat, ") \033[0;34m$\033[0;37m ");
	free(exit_stat);
	new_prompt = ft_strjoin("\033[0;32m(", exit_val);
	free(exit_val);
	exit_val = ft_strjoin(shell->prompt, new_prompt);
	free(new_prompt);
	if (shell->prompt)
		free(shell->prompt);
	shell->prompt = exit_val;
}

static void add_cwd_prompt(t_shell *shell)
{
	char *cwd;

	if (shell->prompt)
		free(shell->prompt);
	cwd = get_cwd(shell);
	if (!cwd)
		shell->prompt = ft_strdup("\033[0;34m");
	else
		shell->prompt = ft_strjoin("\033[0;34m", cwd);
	free(cwd);
}