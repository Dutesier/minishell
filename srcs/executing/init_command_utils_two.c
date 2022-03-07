/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_command_utils_two.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dareias- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 12:18:30 by dareias-          #+#    #+#             */
/*   Updated: 2022/03/05 14:17:14 by dareias-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// For better organization of init command

int	invert_count(int count)
{
	int	ret;

	ret = 0;
	while (count >= 0)
	{
		ret = ret * 10 + (count % 10);
		count = count / 10;
		if (count == 0)
			count = -1;
	}
	return (ret);
}
