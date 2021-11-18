/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dareias- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 18:38:45 by dareias-          #+#    #+#             */
/*   Updated: 2021/11/18 16:15:39 by dareias-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 *
 * Notes: Remenber edge case where a cmm begins with a special char < (or similar)
 * 
*/



int parse_line(t_shell *shell)
{
	int i;
	int c;
	int x;

	i = 0;
	c = 0;

	if (!shell->line)
		return (0);
	shell->commands = malloc(sizeof(t_comm *) * (cmd_ammount(shell->line) + 1));
	if (!shell->commands)
		return (0);

	while (shell->line[i] != '\0')
	{
		// First we initialize a command;
		shell->command[c] = malloc(sizeof(t_comm));
		if (!shell->command[c])
			return (0);

		
		// Run until '<', '>', '<<', '>>' or '|'
		x = i; // Store i
		while (!is_spec(shell->line[i], shell->line[i + 1]))
			i++;
		i--;
		
		// Store the str in a t_comm
		shell->commands[c] = ft_substr(shell->line, x, i - x);
		c++;
	}
}

int is_spec(char c)
{
	if (c == '|' || c == '<' || c == '>')
		return (1);
	return (0);
}

static int cmd_ammount(char *line)
{
	int i;
	int in_cmd;
	int count;

	i = 0;
	in_cmd = 1;
	count = 1;
	while (line[i] != '\0')
	{
		if (is_spec(line[i]))
		{
			if (!in_cmd)
				in_cmd = 1;
			else
				in_cmd = 0;
			if (in_cmd)
				count++;
		}
		i++;
	}
	return (i);
}
