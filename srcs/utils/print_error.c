/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dareias- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 16:12:47 by dareias-          #+#    #+#             */
/*   Updated: 2021/11/17 17:37:10 by dareias-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	print_error(int error)
{
	if (error == 0)
		perror("minishell: ");
	if (error == 1)
		perror("minishell: Failed to allocate memory: ");
	if (error == 2)
		perror("minishell: Couldn't open file: ");
	if (error == 3)
		perror("minishell: Failed to create fork: ");
	return (1);
}
