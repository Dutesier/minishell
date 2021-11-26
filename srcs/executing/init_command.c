/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dareias- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 15:40:52 by dareias-          #+#    #+#             */
/*   Updated: 2021/11/26 12:53:06 by dareias-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int args_ammount(t_ast *command)
{
	int i;
	int count;

	i = 0;
	count = 0;
	while (command->branches[i] != NULL)
	{
		if (command->branches[i++]->my_tok->e_type == TOK_WORD)
			count++;
	}
	return (count + 1);
}

int command_ammount(t_ast *root, int count)
{
	int i;

	i = 0;
	while (root && root->branches && root->branches[i] != NULL)
	{
		count = command_ammount(root->branches[i], count);
		if (root->branches[i]->e_type == AST_COMMAND)
			count++;
		i++;
	}
	if (root->e_type == AST_ROOT)
		printf("Command ammount in %s:  %i\n", ast_to_str(root->e_type), count);
	return (count);
}

int store_args(t_comm *comm, t_ast *ast)
{
	int x;
	int i;

	x = 0;
	i = 0;
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
	return (x);
}

int init_command(t_shell *shell, t_ast *ast) //FIXME only runs with very basic commands
{
	t_comm *comm;
	int a;
	int x;

	a = args_ammount(ast);
	command_ammount(ast, 0);
	x = 0;
	comm = malloc(sizeof(t_comm));
	if (!comm)
		return (1);
	comm->cmd = ft_newpath(ast->branches[0]->my_tok->value, shell->envp);
	if (a > 1)
		x = store_args(comm, ast);
	comm->args[x] = NULL;
	return (run_command(comm));
}

