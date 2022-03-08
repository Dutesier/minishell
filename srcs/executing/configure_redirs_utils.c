#include "minishell.h"

void	create_if_needed(char *filename, int mode)
{
	int i;

	if (filename)
	{
		i = ft_getfd(filename, mode);
		if (i >= 0)
			close(i);
	}
}
