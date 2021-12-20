/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jibanez- < jibanez-@student.42lisboa.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 16:25:59 by Jibanez-          #+#    #+#             */
/*   Updated: 2021/12/20 18:56:10 by dareias-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//static int ft_loop_echo(t_comm *ft_comm, int n);

int ft_echo(t_comm *ft_comm)
{
	char	*str;
	int		n;

	n = 0;
	str = NULL;
	if (ft_comm->out == -1)
		ft_comm->out = STDOUT_FILENO;
	if (ft_comm->args[1])
	{
		if (ft_strcmp(ft_comm->args[1], "-n", ft_min(ft_strlen(ft_comm->args[1]), 2)))
		{
			n = 1;
			str = ft_comm->args[2];
		}
		else
			str = ft_comm->args[1];
	}
	if (str)
		printf("%s", str);
    if (!n)
        printf("\n");
	return (1);
}

/*static int ft_loop_echo(t_comm *ft_comm, int n)
{
	char *str;

	if (ft_comm->in == -1)
		ft_comm->in = STDIN_FILENO;
	while (1)
	{
		str = get_next_line(ft_comm->in, "> ");
		if (!str)
			return (1);
		if (str[0] == '\0')
			return (0);
		prinft("%s", str);
		if (!n)
			printf("\n");
		free(str);
	}
}*/

