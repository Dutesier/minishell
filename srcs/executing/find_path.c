/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jibanez- <jibanez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 16:16:21 by dareias-          #+#    #+#             */
/*   Updated: 2022/03/09 18:55:55 by jibanez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
 *
 * Given an array of possible paths we find the full path to be given to execve
 *
*/

#include "minishell.h"

char	*ft_findpath(char **envp)
{
	int	i;

	i = 0;
	if (!envp || !envp[i])
		return (NULL);
	while (ft_strcmp(envp[i], "PATH", 4) == 0)
		i++;
	return (envp[i]);
}

char	*ft_newpath(char *cmd, char **envp)
{
	int		i;
	char	**path;
	char	*full_cmd;

	i = 0;
	if (access(cmd, X_OK) == 0)
		return (ft_strdup(cmd));
	path = ft_split(ft_findpath(envp), ':');
	while (path[i] != NULL)
	{
		full_cmd = ft_append(path[i], cmd);
		if (access(full_cmd, X_OK) == 0)
			return (full_cmd);
		free(full_cmd);
		i++;
	}
	return (NULL);
}
