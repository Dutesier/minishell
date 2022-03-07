/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dareias- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 15:44:39 by dareias-          #+#    #+#             */
/*   Updated: 2022/03/05 19:10:47 by dareias-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	null_command(t_comm *comm);
static int	child_process(t_comm *comm);

static void	comm_sig(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n");
	}
}

int	run_command(t_comm *comm)
{
	pid_t	pid;
	int		sta;

	if (set_in_and_out(comm))
		return (1);
	if (comm->shell->debug)
	{
		comm_printer(comm);
		fprintf(stderr, "********* FINISHED DEBUGGING *********\n");
		fprintf(stderr, "%sCommand output:%s \n", ft_color(GRN), ft_color(WHT));
	}
	signal(SIGINT, comm_sig);
	if (comm->is_ft)
		return (run_ft_command(comm));
	if (!comm->cmd)
		return (null_command(comm));
	pid = fork();
	if (pid == -1)
		return (print_error(FORK_FAIL));
	if (pid == 0)
		child_process(comm);
	else
	{
		waitpid(pid, &sta, 0);
		DEBUG(fprintf(stderr, "**************Execve finished**************\n"));
		sta = WEXITSTATUS(sta);
		if (sta)
			return (sta);
		return (0);
	}
	return (0);
}

static int	child_process(t_comm *comm)
{
	int	error;

	error = 0;
	DEBUG(fprintf(stderr, "Inside forked process\n"));
	if (!comm->is_ft)
	{
		DEBUG(fprintf(stderr, "Calling execve\n"));
		error = execve(comm->cmd, comm->args, comm->shell->envp);
		if (error < 0)
			return (print_error(-1));
	}
	return (error);
}

static int	null_command(t_comm *comm)
{
	comm->cmd = ft_strcat("minishell: command not found: ", comm->args[0]);
	ft_putstr_fd(comm->cmd, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	return (127);
}

int	run_ft_command(t_comm *ft_comm)
{
	int	sta;
	int	save_in;
	int	save_out;

	sta = 0;
	save_in = STDIN_FILENO;
	save_out = STDOUT_FILENO;
	DEBUG(fprintf(stderr, "Entered run ft\n"));
	sta = exec_ft_comm(ft_comm);
	DEBUG(fprintf(stderr, "Ran ft_command\n"));
	return (sta);
}
