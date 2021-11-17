/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executing.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dareias- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 16:17:04 by dareias-          #+#    #+#             */
/*   Updated: 2021/11/17 17:20:46 by dareias-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTING_H
# define EXECUTING_H


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

char *ft_newpath(char *cmd, char **envp);
char *ft_findpath(char **envp);
int run_command(t_comm *comm);


#endif
