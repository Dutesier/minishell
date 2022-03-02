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

static void	comm_sig(int sig)
{
	if (sig == SIGINT)
	{
	 	printf("\n");
	}
}

int run_command(t_comm *comm)
{
	pid_t	pid;
	int		sta;
	int		error;
	

	error = 0;
	if (set_in_and_out(comm)) // FIXME handle multiple redirs (i.e. ls > test > test1)
		return (1);
	if (comm->shell->debug)
	{
		comm_printer(comm);
		fprintf(stderr,"********* FINISHED DEBUGGING *********\n");
		fprintf(stderr,"%sCommand output:%s \n", ft_color(GRN), ft_color(WHT));
	}
	signal(SIGINT, comm_sig);
	if (comm->is_ft)
		return (run_ft_command(comm));
	if (!comm->cmd)
	{
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
	else
	{
		
		waitpid(pid, &sta, 0);
		DEBUG(fprintf(stderr, "Execve finished\n"));
		sta = WEXITSTATUS(sta);
		if (sta)
			return (sta);
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
	save_in = STDIN_FILENO;
	save_out = STDOUT_FILENO;
	
	DEBUG(fprintf(stderr, "Entered run ft\n"));
	sta = exec_ft_comm(ft_comm); 
	DEBUG(fprintf(stderr, "Ran ft_command\n"));
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
