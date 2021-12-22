/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_variables.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dareias- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 16:24:28 by dareias-          #+#    #+#             */
/*   Updated: 2021/12/22 17:33:43 by dareias-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int add_variable(t_shell *shell, char *var, char *expands)
{
	//printf("Entered add variable\n");
	char **temp;
	int i;

	i = 0;
	if (!shell->vars) // Create a vars table
	{
	//	printf("Creating a vars table\n");
		shell->vars = malloc(sizeof(char *) * 3);
		if (!shell->vars)
			return (0); // or malloc error
		shell->vars[0] = ft_strdup(var);
		shell->vars[1] = ft_strdup(expands);
		shell->vars[2] = NULL;
		return (1);
	}

	while (shell->vars[i] != NULL)
		i++;
	temp = malloc(sizeof(char *) * (i + 3));
	if (!temp)
		return (0);

	i = 0;
	while (shell->vars[i] != NULL)
	{
		temp[i] = shell->vars[i];
		i++;
	}
	temp[i++] = ft_strdup(var);
	temp[i++] = ft_strdup(expands);
	temp[i] = NULL;
	if (shell->vars != NULL)
		free(shell->vars);
	shell->vars = temp;
	return (1);
}

int	set_variable(t_shell *shell, t_ast *ast)
{
	int var;
	int var_def;
	float var_set;
	char *variable;
	char *variable_def;

	/*printf("Entered set variable\n");
	printf("Var %i\n", var);
	printf("Var %s, %i\n", ast->branches[var]->my_tok->value, var);
	printf("Expands %s, %i\n", ast->branches[var_def]->branches[1]->my_tok->value, var_def);*/

	var = find_var_branch(ast);
	var_def = var + 1;
	variable = ast->branches[var]->my_tok->value;
	variable_def = ast->branches[var_def]->branches[1]->my_tok->value;
	var_set = var_is_set(shell, variable);
	if (var_set > -1)
		return (update_var(shell, variable, variable_def, var_set));
	return (add_variable(shell, variable, variable_def));
}

int update_var(t_shell *shell, char *var, char *expands, float var_set)
{
	char *new_env;
	char *temp;
	int	where;

	new_env = NULL;
	temp = NULL;
	where = (int)var_set;
//	printf("updating variable %s where(%i) var_set(%f)\n", var, where, var_set);
	if (var_set - (float)where == 0)
	{
		free(shell->vars[where + 1]);
		shell->vars[where + 1] = ft_strdup(expands);
		if (!shell->vars[where + 1])
			return (1);
		return (0);
	}
	temp = ft_strcat(var, "=");
	if (!temp)
		return (1);
	new_env = ft_strcat(temp, expands);
	if (!new_env)
	{
		free(temp);
		return (1);
	}
	//free(shell->envp[where]); //Should we do this?? It is segfaulting
	shell->envp[where] = new_env;
	free(temp);
	return (0);
}

void exports_log(t_shell *shell, char *var)
{
	int i;
	int size;
	char **temp;

	i = 0;
	size = 0;
	if (!shell->exports)
	{
		shell->exports = malloc(sizeof(char *) * 2);
		if (!shell->exports)
			return ; //or malloc error
		shell->exports[0] = ft_strdup(var);
		shell->exports[1] = NULL;
		return ;
	}
	while (shell->exports[size] != NULL)
		size++;
	temp = malloc(sizeof(char *) * (size + 2));
	if (!temp)
		return ;
	while (shell->exports[i] != NULL)
	{
		temp[i] = shell->exports[i];
		i++;
	}
	temp[i++] = ft_strdup(var);
	temp[i] = NULL;
	free(shell->exports);
	shell->exports = temp;
	return ;
}


int find_var_branch(t_ast *ast)
{
	int i;
	int novar;

	i = 0;
	novar = -1;
	while (ast->branches[i] != NULL)
	{
		if (ast->branches[i]->e_type == AST_VARIABLE)
		{
			novar = 1;
			break ;
		}
		i++;
	}
	if (novar == -1)
		return (novar);
	return (i);
}
