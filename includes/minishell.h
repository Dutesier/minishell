/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dareias- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 14:52:23 by dareias-          #+#    #+#             */
/*   Updated: 2021/11/18 14:04:14 by dareias-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>

# include "commands.h"
# include "executing.h"
# include "utils.h"
# include "redirecting.h"
# include "get_next_line.h"
# include "reader.h"

typedef struct	s_shell
{
	char	**envp;
	char	*line;

	t_comm	**commands;

}			t_shell;

#endif
