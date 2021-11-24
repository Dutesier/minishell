/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dareias- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 15:44:39 by dareias-          #+#    #+#             */
/*   Updated: 2021/11/24 15:10:14 by dareias-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int args_ammount(t_ast *command)
{
	int i;
	int count;

	i = 0;
	count = 0;
	while(command->branches[i] != NULL)
	{
		if (command->branches[i++]->my_tok->e_type == TOK_WORD)
			count++;
	}
	return (count + 1);
}

int init_command(t_shell *shell, t_ast *ast) //FIXME only runs with very basic commands
{
	t_comm *comm;
	int i;
	int x;

	i = 0;
	x = 0;
	comm = malloc(sizeof(t_comm));
	if (!comm)
		return (1);
	comm->cmd = ft_newpath(ast->branches[0]->my_tok->value, shell->envp);
	comm->args = malloc(sizeof(char *) * (args_ammount(ast->branches[1]) + 1));
	if (!comm->args)
		return (1);
	comm->args[x++] = ast->branches[0]->my_tok->value;
	while (ast->branches[1]->branches[i] != NULL)
	{
		if (ast->branches[1]->branches[i]->my_tok->e_type == TOK_SPACE)
			i++;
		else
			comm->args[x++] = ast->branches[1]->branches[i++]->my_tok->value;
	}
	comm->args[x] = NULL;
	x = 0;
	while(comm->args[x] != NULL)
		printf("%s\n", comm->args[x++]);
	return (run_command(comm));
}

int run_command(t_comm *comm)
{
	pid_t	pid;
	int		sta;
	int		error;
	

	pid = fork();
	if (pid == -1)
		return (print_error(FORK_FAIL));
	if (pid == 0)
	{
		if (set_in_and_out(comm))
			return (1);

		error = execve(comm->cmd, comm->args, NULL);
		if (error < 0)
			return (print_error(EXEC_FAIL));
	}
	else
	{
		waitpid(pid, &sta, 0);
		sta = WEXITSTATUS(sta);
		if (sta)
			return (1);
		return (0);
	}
	return (0);
}
