/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dareias- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 15:40:52 by dareias-          #+#    #+#             */
/*   Updated: 2021/12/06 16:54:54 by dareias-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int args_ammount(t_ast *command)
{
	int i;
	int count;

	i = 0;
	count = 0;
	//printf("Entered args_ammount for ast branch %s \n", ast_to_str(command->e_type));
	while (command && command->branches && command->branches[i] != NULL)
	{
		if (command->branches[i++]->my_tok->e_type == TOK_WORD)
			count++;
	}
	//printf("left args_ammount with %i\n", count + 1);
	return (count + 1);
}

int compound_ammount(t_ast *root, int count)
{
	int i;

	i = 0;
	while (root && root->branches && root->branches[i] != NULL)
	{
		count = compound_ammount(root->branches[i], count);
		if (root->branches[i]->e_type == AST_COMPOUND)
			count++;
		i++;
	}
	if (root->e_type == AST_ROOT)
		printf("Compound ammount in %s:  %i\n", ast_to_str(root->e_type), count);
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

t_comm *init_command(t_shell *shell, t_ast *ast) //FIXME only runs with very basic commands
{
	t_comm *comm;
	int a;
	int x;

//	printf("Entered init_command of ast branch %s \n", ast_to_str(ast->e_type));
	if (ast->branches[1] == NULL)
		a = 0;
	else
		a = args_ammount(ast->branches[1]);
	x = 0;
	comm = malloc(sizeof(t_comm));
	if (!comm)
		return (NULL);

	if (ast->branches[0]->e_type == AST_VARIABLE)
		comm->e_type = VAR_DEF;
	else
		comm->e_type = COMMAND;
	comm->cmd = ft_newpath(ast->branches[0]->my_tok->value, shell->envp);
	if (a > 1)
	{
		x = store_args(comm, ast);
		comm->args[x] = NULL;
	}
	else
	{
		comm->args = malloc(sizeof(char *) * 2);
		if (!comm->args)
			return (NULL); // NOT A CLEAN EXIT FIXME
		comm->args[0] = ast->branches[0]->my_tok->value;
		comm->args[1] = NULL;
	}
	//printf("Left init_command \n");
	return (comm);
}

