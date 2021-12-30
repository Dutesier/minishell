/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dareias- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 15:44:39 by dareias-          #+#    #+#             */
/*   Updated: 2021/12/30 18:56:20 by dareias-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int run_command(t_comm *comm)
{
	pid_t	pid;
	int		sta;
	int		error;
	

	if (comm->is_ft)
		return (run_ft_command(comm));
	if (!comm->cmd)
	{
		if (comm->fd_p[0] > -1)
		{
			close(comm->fd_p[0]);
			close(comm->fd_p[1]);
		}
		comm->cmd = ft_strcat("minishell: command not found: ", comm->args[0]);
		ft_putstr_fd(comm->cmd, STDERR_FILENO);
		ft_putstr_fd("\n", STDERR_FILENO);
		return (1);
	}
	pid = fork();
	if (pid == -1)
		return (print_error(FORK_FAIL));
	if (pid == 0)
	{

		if (set_in_and_out(comm)) // FIXME handle multiple redirs (i.e. ls > test > test1)
			return (1);

		error = execve(comm->cmd, comm->args, comm->shell->envp);
		if (error < 0)
			return (print_error(-1));
	}
	else
	{
		if (comm->fd_p[0] > -1)
		{
			close(comm->fd_p[0]);
			close(comm->fd_p[1]);
		}
		waitpid(pid, &sta, 0);
		sta = WEXITSTATUS(sta);
		if (sta)
			return (1);
		return (0);
	}
	return (0);
}

int run_ft_command(t_comm *ft_comm)
{
	int sta;
	int save_in;
	int save_out;

	sta = 0;
	save_in = dup(STDIN_FILENO);
	save_out = dup(STDOUT_FILENO);
	if (set_in_and_out(ft_comm))
		return (1);
	sta = exec_ft_comm(ft_comm); 
	if (ft_comm->fd_p[0] > -1)
	{
		close(ft_comm->fd_p[0]);
		close(ft_comm->fd_p[1]);
	}
	if (ft_comm->infile)
	{
		dup2(save_in, STDIN_FILENO);
		close(ft_comm->in);
	}
	if (ft_comm->outfile)
	{
		dup2(save_out, STDOUT_FILENO);
		close(ft_comm->out);
	}
	return (sta);
}

int exec_ft_comm(t_comm *ft_comm)
{
	if (ft_comm->is_ft == 1)
		return (ft_cd(ft_comm));
	if (ft_comm->is_ft == 2)
		return (ft_pwd(ft_comm));
	if (ft_comm->is_ft == 3)
		return (ft_echo(ft_comm));
	if (ft_comm->is_ft == 4)
		return (ft_env(ft_comm, 0));
	if (ft_comm->is_ft == 5)
		return (ft_export(ft_comm));
	if (ft_comm->is_ft == 6)
		return (ft_unset(ft_comm));
	if (ft_comm->is_ft == 7)
		ft_exit(ft_comm);
	return (-1);
}
