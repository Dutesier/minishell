/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   canonical_mode.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jibanez- <jibanez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/29 18:01:00 by jibanez-          #+#    #+#             */
/*   Updated: 2022/01/12 19:16:02 by jibanez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "canonical.h"

void	init_termcaps(t_shell *shell)
{
	char	*term_type;

	if (tcgetattr(STDIN_FILENO, &shell->termcaps.old_term) == -1)
		handle_error(shell, EXIT_FAILURE);
	term_type = ft_find_value_from_key("TERM", shell->envp);
	if (!term_type)
		handle_error(shell, EXIT_FAILURE);
	if (tgetent(shell->termcaps.buffer, term_type) <= 0)
		handle_error(shell, EXIT_FAILURE);
	// else if (!capabilities(&shell->termcaps))
	// 	handle_error(shell, EXIT_FAILURE);
	free(term_type);
}

// void	canonical_on()
// {

// }

// void	canonical_off()
// {

// }

// https://arcticfox1919.gitee.io/linux-manual/man-pages/man5/terminfo.5.html

int	capabilities(t_termcaps *termcaps)
{
	int	check;

	termcaps->keys_on = tgetstr("ks", &termcaps->buffer);
	write(1, "HERE\n", 6);
	if (termcaps->keys_on)
		tputs(termcaps->keys_on, 1, ft_putint);
	// termcaps->keys_off = tgetstr("ke", &termcaps->buffer);
	// else (IS_LINUX)
		// termcaps->backspace = tgetstr("kb", &termcaps->buffer);
	termcaps->backspace = ft_strdup("\x7f");
	termcaps->del_line = tgetstr("dl", &termcaps->buffer);
	termcaps->set_cursor_begin = tgetstr("cr", &termcaps->buffer);
	if (!termcaps->keys_on || !termcaps->keys_off
		|| !termcaps->backspace || !termcaps->del_line
		|| !termcaps->set_cursor_begin)
		check = 0;
	else
		check = 1;
	return (check);
}

char	*ft_find_value_from_key(const char *str, char **envp)
{
	int i;
	int j;
	char *ret;

	i = -1;
	while (envp[++i] != NULL)
	{
		j = 0;
		if (ret && ft_strnstr(envp[i], str))
		{
			while (str[j] && envp[i][j] && (str[j] == envp[i][j]))
				j++;
			if (str[j] == '\0' && (envp[i][j] == '\0' || envp[i][j] == '='))
				ret = ft_strdup(envp[i] + j + 1);
		}
	}
	return (ret);
}