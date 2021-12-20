/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dareias- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 15:31:38 by dareias-          #+#    #+#             */
/*   Updated: 2021/12/20 19:04:24 by dareias-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMANDS_H
# define COMMANDS_H

int ft_cd(t_comm *ft_comm);
int ft_pwd(t_comm *ft_comm);
int ft_echo(t_comm *ft_comm);
int ft_env(t_comm *ft_comm, int exp);
int	ft_export(t_comm *ft_comm);
int ft_unset(t_comm *ft_comm);

// Envp
char **add_envp(char **envp, char *add);
char **rm_envp(char **envp, char *rm);
char *whole_var(t_comm *comm, char *var);

#endif
