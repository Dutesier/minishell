/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_variables.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dareias- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 16:24:28 by dareias-          #+#    #+#             */
/*   Updated: 2021/12/17 18:39:28 by dareias-         ###   ########.fr       */
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
		shell->vars = malloc(sizeof(char *) * 1);
		if (!shell->vars)
			return (0); // or malloc error
		shell->vars[0] = NULL;
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
	/*temp[i] = malloc(sizeof(char *) * ft_strlen(var));
	if (!temp[i++])
		return (0); // FIXME not clean exit
	temp[i] = malloc(sizeof(char *) * ft_strlen(expands));
	if (!temp[i])
		return (0); // FIXME not clean exit*/
	temp[i] = NULL;
	if (shell->vars)
		free(shell->vars);
	shell->vars = temp;
	return (1);
}

int	set_variable(t_shell *shell, t_ast *ast)
{
	int var;
	int var_def;

	var = find_var_branch(ast);
	var_def = var + 1;
	/*printf("Entered set variable\n");
	printf("Var %i\n", var);
	printf("Var %s, %i\n", ast->branches[var]->my_tok->value, var);
	printf("Expands %s, %i\n", ast->branches[var_def]->branches[1]->my_tok->value, var_def);*/
	return (add_variable(shell, ast->branches[var]->my_tok->value, ast->branches[var_def]->branches[1]->my_tok->value));
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
