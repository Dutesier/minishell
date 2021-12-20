/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jibanez- < jibanez-@student.42lisboa.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 17:17:56 by Jibanez-          #+#    #+#             */
/*   Updated: 2021/12/20 18:07:23 by dareias-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_env(t_comm *ft_comm, int exp)
{
    int i;

    i = 0;
    while (ft_comm->envp[i])
    {
		if (exp)
			printf("declare -x ");
		printf("%s\n", ft_comm->envp[i]);
		i++;
    }
	return (1);
}
