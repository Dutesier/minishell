#include "minishell.h"

char	*get_cwd(t_shell *shell)
{
	char	*cwd;
	int		i;
	int		j;

	i = 0;
	if (!shell->envp || !shell->envp[i])
		return (NULL);
	while (shell->envp[i] && ft_strcmp(shell->envp[i], "PWD", 3) == 0)
		i++;
	if (!shell->envp[i])
		return (NULL);
	j = ft_strlen(shell->envp[i]);
	while (j >= 0 && shell->envp[i][j] != '/')
		j--;
	if (j == 0 && shell->envp[i][j] == '/')
		return (NULL);
	cwd = ft_substr(shell->envp[i], j + 1, ft_strlen(shell->envp[i]) - (j + 1));
	return (cwd);
}
