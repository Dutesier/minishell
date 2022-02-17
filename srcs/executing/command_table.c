/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_table.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jibanez- <jibanez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 15:58:18 by dareias-          #+#    #+#             */
/*   Updated: 2022/02/15 18:54:46 by jibanez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	comm_table_pipes(t_shell *shell, t_ast *root);

int	command_table(t_shell *shell, t_ast *root)
{
	int	count;
	int	i;
	int	x;

	count = compound_ammount(root, 0);
	i = 0;
	x = 0;
	shell->commands = malloc(sizeof(t_comm *) * (count + 1));
	if (!shell->commands)
		return (0);
	while (i < count)
	{
		if (root->branches[i + x]->e_type == AST_WORD)
			x++;
		shell->commands[i] = init_command(shell, root->branches[i + x]);
		i++;
	}
	shell->commands[i] = NULL;
	comm_table_pipes(shell, root);
	return (i);
}

static void	set_as_piper(t_shell *shell, int i, int fd[])
{
	if (shell->commands[i]->piping == 0)
		shell->commands[i]->piping = 2;
	else
		shell->commands[i]->piping = 3;
	/*shell->commands[i]->fd_n[0] = fd[0];
	shell->commands[i]->fd_n[1] = fd[1];*/
	shell->commands[i]->my_pipe[0] = fd[0];
	shell->commands[i]->my_pipe[1] = fd[1];
}

static void	set_as_piped(t_shell *shell, int i, int fd[])
{
	if (shell->commands[i]->piping == 0)
		shell->commands[i]->piping = 1;
	else
		shell->commands[i]->piping = 3;
	/*shell->commands[i]->fd_p[0] = fd[0];
	shell->commands[i]->fd_p[1] = fd[1];*/
	shell->commands[i]->my_pipe[0] = fd[0];
	shell->commands[i]->my_pipe[1] = fd[1];
}

/* this should be done for every command */
static int	comm_table_pipes(t_shell *shell, t_ast *root)
{
	int	i;
	int	x;
	int used;
	int	fd[2];

	i = 0;
	x = 0;
	used = 0;
	if (pipe(fd) < 0)
		return (0);
	while (root->branches && root->branches[x])
	{
		if (root->branches[x]->e_type == AST_WORD)
		{
			if (x > 0)
			{
				set_as_piper(shell, i - 1, fd);
				used = 1;
			}
			if (shell->commands[i] != NULL)
			{
				set_as_piped(shell, i, fd);
				used = 1;
			}
			x++;
		}
		i++;
		x++;
	}
	if (!used)
	{
		close(fd[0]);
		close(fd[1]);
	}
	return (i);
}

int	run_comm_table(t_shell *shell)
{
	int	i;

	i = 0;
	while (shell->commands && shell->commands[i] != NULL)
	{
		if (shell->debug)
		{
			comm_printer(shell->commands[i]);
			printf("********* FINISHED DEBUGGING *********\n");
			printf("%sCommand output:%s \n", ft_color(GRN), ft_color(WHT));
		}
		if (shell->commands[i]->e_type == VAR_DEF)
		{
			if (shell->debug)
			{
				if (shell->commands[i]->redir == 1)
					printf("%sVariable set%s \n", ft_color(BLU), ft_color(WHT));
				else
					printf("%sWarning: Either rewrote variable or variable couldn't be set%s \n", ft_color(RED), ft_color(WHT));
			}
			i++;
		}
		else if (shell->commands[i]->e_type == INVALID)
			i++;
		else
		{
			shell->last_exit = run_command(shell->commands[i]);
			reset_std_io(shell->commands[i++], 1, 1);
			close_std_io_dups(shell);
		}
	}
	return (i);
}
