#include "minishell.h"

void	expand(t_shell *shell, char **exp)
{
	char	*temp;

	temp = ft_variable(shell, *exp);
	DEBUG(fprintf(stderr, "Variable from ft_variable: %s", temp));
	safe_free(*exp);
	*exp = temp;
	DEBUG(fprintf(stderr, "Variable from ft_variable: %s", *exp));
}

char	*remove_old(char *s, int where)
{
	char 	*temp;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (exp_valid_format(s, (where + 1) + i))
		i++;
	if(!s)
	{
		DEBUG(fprintf(stderr, "Panic, why am I null????\n");)
		return (NULL);
	}
	DEBUG(fprintf(stderr,"Deleting %i elements\n Mallocing %i bytes\nWhere: %i\nOur str: %s\n", i, ft_strlen(s) - i, where, s));
	temp = malloc_or_exit(sizeof(char) * (ft_strlen(s) - i));
	while (s[j] != '\0' && j < where)
	{
		temp[j] = s[j];
		j++;
	}
	while (s[j + i + 1] != '\0')
	{
		temp[j] = s[j + i + 1];
		j++;
	}
	temp[j] = '\0';
	DEBUG(fprintf(stderr, "STR without $VAR: %s\n", temp));
	safe_free(s);
	return (temp);
}
