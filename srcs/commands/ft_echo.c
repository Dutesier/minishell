/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jibanez- <jibanez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 16:25:59 by Jibanez-          #+#    #+#             */
/*   Updated: 2022/02/14 16:16:58 by dareias-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//static int ft_loop_echo(t_comm *ft_comm, int n);

int ft_echo(t_comm *ft_comm)
{
	printf("Entered ft_echo\n");
	char	*str;
	int		n;
	int		i;

	n = 0;
	i = 1;
	str = NULL;
	if (ft_comm->out == -1)
		ft_comm->out = STDOUT_FILENO;
	if (ft_comm->args[1])
	{
		if (ft_strcmp(ft_comm->args[1], "-n", ft_min(ft_strlen(ft_comm->args[1]), 2))) // This needs to be changed
		{
			n = 1;
			i = 2;
		}
		str = ft_comm->args[i];
	}
	while (ft_comm->args[i])
	{
		printf("%s", ft_comm->args[i++]);
		if (ft_comm->args[i])
			printf(" ");
	}
	if (n == 0)
		printf("\n");
	return (0);
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

