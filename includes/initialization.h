#ifndef INITIALIZATION_H
# define INITIALIZATION_H

# include "minishell.h"

void	init_shell(t_shell *shell, char **envp);
void	handle_sig(int sig);

#endif