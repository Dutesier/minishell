#include "minishell.h"

void	rm_var(t_shell *shell, char *var, int size)
{
	int		i;
	char	**temp;

	i = 0;
	temp = malloc_or_exit(sizeof(char *) * (size - 1));
	size = 0;
	while (shell->vars[i] != NULL || i % 2 != 0)
	{
		if (ft_strcmp_two(shell->vars[i], var))
		{
			free(shell->vars[i++]);
			if (shell->vars[i++])
				free(shell->vars[i]);
		}
		if (shell->vars[i])
			temp[size++] = shell->vars[i++];
	}
	temp[size] = NULL;
	if (shell->vars)
		free(shell->vars);
	shell->vars = temp;
	return ;
}

int	find_next_eq(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i++] == '=')
			break ;
	}
	return (i);
}
