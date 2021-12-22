/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_envp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dareias- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 18:16:14 by dareias-          #+#    #+#             */
/*   Updated: 2021/12/22 17:42:39 by dareias-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char **add_envp(char **envp, char *add)
{
	int i;
	char **new;

	i = 0;
	while (envp[i])
		i++;
	new = malloc(sizeof(char *) * (i + 2)); // one for null and one for the new one
	if (!new)
		return (NULL); // actually return print error of malloc fail
	i = 0;
	while (envp[i])
	{
		new[i] = envp[i]; // Do we want do strdup or are we fine with having just pointers to the OG?
		i++;
	}
	new[i++] = add;
	new[i] = NULL;
	return (new);
}

char **rm_envp(char **envp, char *rm, char **exports)
{
	//printf("Removing %s from envp**\n", rm);
	int i;
	int j;
	int l;
	char **new;

	i = 0;
	j = 0;
	l = 0;
	if (!envp || !envp[j])
		return (NULL);
	while (envp[j])
		j++;
	new = malloc(sizeof(char *) * (j)); // add one for null and remove one for the old one
	if (!new)
		return (NULL); // actually return print error of malloc fail
	while (envp[i])
	{
		if (ft_strcmp_two(rm, envp[i]))
		{
			if (did_i_export(rm, exports))
			{
				//printf("Freeing envp[%i]: %s\n", i, envp[i]);
				free(envp[i]);
			}
			//printf("NOT adding %s to new envp\n", rm);
			i++;
		}
		if (envp[i] == NULL)
		{
			break ;
		}
		new[l] = envp[i]; // Do we want do strdup or are we fine with having just pointers to the OG?
		i++;
		l++;
	}
	new[l] = NULL;
	if (i == l)
	{
		//printf("i(%i) == l(%i)\n", i, l);
		free(new);
		return (envp);
	}
	return (new);
}

char *whole_var_from_vars(char **vars, char *var)
{
	int i;
	char *temp;
	char *final;

	i = 0;
	if (!vars || !vars[0])
		return (NULL);
	while (vars[i])
	{
		if (ft_strcmp_two(vars[i], var))
			 break ;
		i = i + 2;
	}
	if (!vars[i])
		return (NULL);
	temp = ft_strcat(vars[i], "=");
	final = ft_strcat(temp, vars[i + 1]);
	free(temp);
	return (final);
}

void rm_var_from_vars(t_shell* shell, char *var)
{
	//printf("Removing %s from vars**\n", var);
	int i;
	int size;
	int var_set;
	char **temp;

	i = 0;
	size = 0;
	var_set = 0;
	if (!shell->vars || !shell->vars[i])
		return ;
	while (shell->vars[size] != NULL)
		size++;
	//printf("SIZE of new vars : %i\n", size - 1);
	if (size == 0)
		return ;//((void)printf("Vars is already empty\n"));
	while (shell->vars[i] != NULL)
	{
		if (ft_strcmp_two(shell->vars[i], var))
			var_set = 1;
		i++;
	}
	if (!var_set)
	{
		//printf("<---N/A\n");
		return ;
	}
	temp = malloc(sizeof(char *) * (size - 1)); // +1 for null -2 to delete vars
	if (!temp)
		return ;
	i = 0;
	size = 0;
	while (shell->vars[i] != NULL)
	{
		if (ft_strcmp_two(shell->vars[i], var))
		{
		//	printf("i %i\n", i);
			free(shell->vars[i++]);
		//	printf("i %i\n", i);
			free(shell->vars[i++]);
		}
		if (shell->vars[i])
			temp[size++] = shell->vars[i++];
	}
	temp[size] = NULL;
	if (shell->vars)
		free(shell->vars);
	shell->vars = temp;
	return ;
}

int did_i_export(char *var, char **exports)
{
	int i;

	i = 0;
	while (exports && exports[i] != NULL)
	{
		if (ft_strcmp_two(var, exports[i]))
			return (1);
		i++;
	}
	return (0);
}
