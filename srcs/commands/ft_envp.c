/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_envp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dareias- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 18:16:14 by dareias-          #+#    #+#             */
/*   Updated: 2021/12/20 19:22:00 by dareias-         ###   ########.fr       */
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

char **rm_envp(char **envp, char *rm)
{
	int i;
	int j;
	char **new;

	i = 0;
	j = 0;
	while (envp[j])
		j++;
	new = malloc(sizeof(char *) * (j)); // add one for null and remove one for the old one
	if (!new)
		return (NULL); // actually return print error of malloc fail
	while (envp[i])
	{
		if (ft_strcmp(rm, envp[i], ft_min(ft_strlen(envp[i]), ft_strlen(rm))))
			free(envp[i++]);
		new[i] = envp[i]; // Do we want do strdup or are we fine with having just pointers to the OG?
		i++;
	}
	new[i] = NULL;
	if (i == j)
	{
		free(new);
		return (NULL);
	}
	return (new);
}

char *whole_var(t_comm *comm, char *var)
{
	int i;
	char *temp;
	char *final;

	i = 0;
	if (!comm->vars || !comm->vars[0])
		return (NULL);
	while (comm->vars[i])
	{
		if (ft_strcmp(comm->vars[i], var, ft_min(ft_strlen(var), ft_strlen(comm->vars[i]))))
			 break ;
		i = i + 2;
	}
	if (!comm->vars[i])
		return (NULL);
	temp = ft_strcat(comm->vars[i], "=");
	final = ft_strcat(temp, comm->vars[i + 1]);
	free(temp);
	return (final);
}

