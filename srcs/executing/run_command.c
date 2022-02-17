/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dareias- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 15:44:39 by dareias-          #+#    #+#             */
/*   Updated: 2022/02/14 16:19:27 by dareias-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int run_command(t_comm *comm)
{
	pid_t	pid;
	int		sta;
	int		error;
	

	error = 0;
	if (set_in_and_out(comm)) // FIXME handle multiple redirs (i.e. ls > test > test1)
		return (1);
	if (comm->is_ft)
		return (run_ft_command(comm));
	if (!comm->cmd)
	{
		/*if (comm->fd_p[0] > -1)
		{
			fprintf(stderr, "Closing comm->fd_p[0]: (%i)\n",comm->fd_p[0]);
			close(comm->fd_p[0]);
			fprintf(stderr, "Closing comm->fd_p[1]: (%i)\n",comm->fd_p[0]);
			close(comm->fd_p[1]);
		}*/
		comm->cmd = ft_strcat("minishell: command not found: ", comm->args[0]);
		ft_putstr_fd(comm->cmd, STDERR_FILENO);
		ft_putstr_fd("\n", STDERR_FILENO);
		return (127);
	}
	pid = fork();
	if (pid == -1)
		return (print_error(FORK_FAIL));
	if (pid == 0)
	{

		fprintf(stderr, "Inside forked process\n");


		comm_printer(comm);
		if (!comm->is_ft)
		{
			fprintf(stderr, "Calling execve\n");
			error = execve(comm->cmd, comm->args, comm->shell->envp);
			if (error < 0)
				return (print_error(-1));
		}
		return (error);
	}
	else
	{
		/*if (comm->fd_p[0] > -1)
		{
			fprintf(stderr, "Closing comm->fd_p[0]: (%i)\n",comm->fd_p[0]);
			close(comm->fd_p[0]);
			fprintf(stderr, "Closing comm->fd_p[1]: (%i)\n",comm->fd_p[1]);
			close(comm->fd_p[1]);
		}*/
		waitpid(pid, &sta, 0);
		fprintf(stderr, "Execve finished\n");
		sta = WEXITSTATUS(sta);
		if (sta)
			return (sta);
		return (0);
	}
	return (0);
}

int run_ft_command(t_comm *ft_comm)
{
	printf("Entered run ft\n");
	int sta;
	int save_in;
	int save_out;

	sta = 0;
	save_in = STDIN_FILENO;
	save_out = STDOUT_FILENO;
	//if (set_in_and_out(ft_comm))
	//	return (1);
	fprintf(stderr, "Entered run ft\n");
	comm_printer(ft_comm);
	sta = exec_ft_comm(ft_comm); 
	fprintf(stderr, "Ran ft_command\nClosing Pipes\n");
	/*if (ft_comm->fd_p[0] > -1)
	{
		fprintf(stderr, "Closing previous pipe\n");
		fprintf(stderr, "Closing ft_comm->fd_p[0]: (%i)\n", ft_comm->fd_p[0]);
		close(ft_comm->fd_p[0]);
		fprintf(stderr, "Closing ft_comm->fd_p[1]: (%i)\n", ft_comm->fd_p[1]);
		close(ft_comm->fd_p[1]);
	}
	if (ft_comm->infile)
	{
		fprintf(stderr, "Resseting STDIN\n");
		dup2(save_in, STDIN_FILENO);
		fprintf(stderr, "Closing ft_comm->in: (%i)\n", ft_comm->in);
		close(ft_comm->in);
	}
	if (ft_comm->outfile)
	{
		fprintf(stderr, "Resseting STDOUT\n");
		dup2(save_out, STDOUT_FILENO);
		fprintf(stderr, "Closing ft_comm->out: (%i)\n", ft_comm->out);
		close(ft_comm->out);
	}*/
	fprintf(stderr, "Returning from run_ft_command\n");
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
