/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dareias- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 15:40:52 by dareias-          #+#    #+#             */
/*   Updated: 2022/01/10 18:09:36 by dareias-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void init_comm_helper(t_comm *comm);

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
		//printf("Compound ammount in %s:  %i\n", ast_to_str(root->e_type), count);
	return (count);
}

int store_args(t_comm *comm, t_ast *ast, int a)
{
	int x;
	int i;
	int	ar;

	x = 0;
	i = 0;
	ar = find_args_branch(ast);
	comm->args = malloc(sizeof(char *) * (a + 1));
	if (!comm->args)
		return (1);
	comm->args[x++] = ast->branches[find_cmd_branch(ast)]->my_tok->value;
	while (ar >= 0)
	{
		while (ast->branches[ar % 10]->branches[i] != NULL)
		{
			if (ast->branches[ar % 10]->branches[i]->my_tok->e_type == TOK_SPACE)
				i++;
			else if (ast->branches[ar % 10]->branches[i]->e_type == AST_VAR_EXP)
			{
				comm->args[x++] = var_expand(ast->branches[ar % 10]->branches[i++]);
				i++;
			}
			else
			{
				//printf("Storing %s", tok_to_str(ast->branches[ar%10]->branches[i]->my_tok->e_type));
				comm->args[x++] = ast->branches[ar % 10]->branches[i++]->my_tok->value;
			}
		}
		ar = ar / 10;
		if (ar == 0)
			ar = -1;
	}
	return (x);
}

t_comm *init_command(t_shell *shell, t_ast *ast) //FIXME only runs with very basic commands
{
	t_comm *comm;
	int a;
	int x;
	int c;

	x = 0;
	a = 0;
	//printf("Entered init_command of ast branch %s \n", ast_to_str(ast->e_type));

	comm = malloc(sizeof(t_comm));
	if (!comm)
		return (NULL);
	init_comm_helper(comm);
	comm->shell = shell;
	replace_variables(shell, ast, NULL);
	if (variable_as_cmd(ast))
	{
		comm->e_type = INVALID;
		return (comm);
	}
	if (*shell->debug)
	{
		int v = 0;
		while (shell->vars && shell->vars[v] != NULL)
		{
			printf("%sVARS[%i]%s%s\n", ft_color(YEL), v, shell->vars[v], ft_color(WHT));
			v++;
		}
	}

	// Setup Command
	c = find_cmd_branch(ast);
	if (find_var_branch(ast) != -1)
	{
		comm->e_type = VAR_DEF;
		comm->redir = set_variable(shell, ast);
		return (comm);
	}
	else
		comm->e_type = COMMAND;
	comm->is_ft = ft_iscomm(ast->branches[c]->my_tok->value);
	comm->cmd = ft_newpath(ast->branches[c]->my_tok->value, shell->envp);

	// Setup arguments
	int ar = find_args_branch(ast);
	while (ar >= 0)
	{
		a += args_ammount(ast->branches[ar % 10]);
		ar = ar / 10;
		if (ar == 0)
			ar = -1;
	}

	if (a > 1)
	{
		x = store_args(comm, ast, a);
		comm->args[x] = NULL;
	}
	else
	{
		comm->args = malloc(sizeof(char *) * 2);
		if (!comm->args)
			return (NULL); // NOT A CLEAN EXIT FIXME
		comm->args[0] = ast->branches[c]->my_tok->value;
		comm->args[1] = NULL;
	}

	// Setup Redirection
	int red;

	red = find_redir_branch(ast);
	while (red >= 0)
	{
		init_comm_redir(comm, ast, red % 10);
		red = red / 10;
		if (red == 0)
			red = -1;
	}
	return (comm);
}

void init_comm_helper(t_comm *comm)
{
	comm->args = NULL;
	comm->infile = NULL;
	comm->cmd = NULL;
	comm->outfile = NULL;
	comm->heredoc = NULL;
	comm->in = -1;
	comm->out = -1;
	comm->redir = 0;

	comm->piping = 0;

	comm->fd_n[0] = -1;
	comm->fd_n[1] = -1;
	comm->fd_p[0] = -1;
	comm->fd_p[1] = -1;

	comm->is_ft = 0;
}

