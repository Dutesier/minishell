#include "minishell.h"

int	var_already_set(t_shell *shell, char *expands, int where)
{
	safe_free(shell->vars[where + 1]);
	shell->vars[where + 1] = ft_strdup(expands);
	if (!shell->vars[where + 1])
		return (1);
	return (0);
}
