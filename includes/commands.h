/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dareias- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 15:31:38 by dareias-          #+#    #+#             */
/*   Updated: 2022/02/06 01:01:26 by dareias-         ###   ########.fr       */
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
void	ft_exit(t_comm *ft_comm);

// Envp
char **add_envp(char **envp, char *add);
char **rm_envp(char **envp, char *rm, char **exports);
char *whole_var_from_vars(char **vars, char *var);
void rm_var_from_vars(t_shell *shell, char *var);
int did_i_export(char *var, char **exports);

// EXPORT
int ft_print_export(t_comm *ft_comm, int i);
int env_in_sorted(char **sorted_env, char *env);
void print_sorted_env(char **sorted_env);
int get_next_lowest_env(char **sorted_env, t_comm *ft_comm);


#endif
