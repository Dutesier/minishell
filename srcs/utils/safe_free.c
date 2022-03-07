#include "minishell.h"

int	safe_free(void *ptr)
{
	if (!ptr)
		return (1);
	else
		free(ptr);
	return (0);
}
