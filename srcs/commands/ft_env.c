/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jibanez- < jibanez-@student.42lisboa.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 17:17:56 by Jibanez-          #+#    #+#             */
/*   Updated: 2021/12/22 15:23:02 by dareias-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_env(t_comm *ft_comm, int exp)
{
    int i;

    i = 0;
	if (!ft_comm->shell->envp)
		return (1);
    while (ft_comm->shell->envp[i])
    {
		if (exp)
			printf("declare -x ");
		printf("%s\n", ft_comm->shell->envp[i]);
		i++;
    }
	return (0);
}
