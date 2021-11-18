/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dareias- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 19:56:38 by dareias-          #+#    #+#             */
/*   Updated: 2021/11/18 19:58:54 by dareias-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H

typedef struct s_comm
{
	char	*infile;
	char	*outfile;
	int		in;
	int		out;

	char	*cmd;
	char	**args;

	int		piping; // If its 0 then we are not piping 1->getting piped 2->piping someone 3->both

	int		fd_p[2]; // Pipe I'm reading from
	int		fd_n[2]; // Pipe I'm writing to;

}			t_comm;

typedef struct	s_shell
{
	char	**envp;
	char	*line;

	t_comm	**commands; // table of all cmommands

}			t_shell;

#endif
