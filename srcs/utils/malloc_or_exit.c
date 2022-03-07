#include "minishell.h"

void *malloc_or_exit(size_t size)
{
	void	*ret;

	ret = malloc(size);
	if (!ret)		
	{
		exit (print_error(MEMORY_FAIL));
	}
	return (ret);
}