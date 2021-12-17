/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executing.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dareias- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 16:17:04 by dareias-          #+#    #+#             */
/*   Updated: 2021/12/17 19:34:25 by dareias-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTING_H
# define EXECUTING_H

char *ft_newpath(char *cmd, char **envp);
char *ft_findpath(char **envp);
int run_command(t_comm *comm);
t_comm *init_command(t_shell *shell, t_ast *ast);
int init_comm_redir(t_comm *comm, t_ast *ast, int r);
int config_redir(t_comm *comm, t_ast *ast, int redir);
int find_cmd_branch(t_ast *ast);
int find_redir_branch(t_ast *ast);
int find_args_branch(t_ast *ast);
int args_ammount(t_ast *command);
int compound_ammount(t_ast *root, int count);
int store_args(t_comm *comm, t_ast *ast, int a);
int ast_handler(t_shell *shell, t_ast *root);
int branch_ammount(t_ast *ast);
int	command_table(t_shell *shell, t_ast *root);
int run_comm_table(t_shell *shell);

char *var_expand(t_ast *ast);
char *ft_variable(t_shell *shell, char *str);
void replace_variables(t_shell *shell, t_ast *ast, t_ast *father);
void ast_update(t_ast *parent, t_ast *child, int up);

int add_variable(t_shell *shell, char *var, char *expands);
int	set_variable(t_shell *shell, t_ast *ast);
int find_var_branch(t_ast *ast);

#endif
