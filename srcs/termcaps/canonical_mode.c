/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   canonical_mode.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jibanez- <jibanez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/29 18:01:00 by jibanez-          #+#    #+#             */
/*   Updated: 2022/01/30 00:52:36 by jibanez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "canonical.h"

void	termcaps_to_null(t_termcaps *termcaps)
{
	termcaps->buffer = NULL;
	termcaps->keys_on = NULL;
	termcaps->keys_off = NULL;
	termcaps->up_arrow = NULL;
	termcaps->down_arrow = NULL;
	termcaps->backspace = NULL;
	termcaps->del_line = NULL;
	termcaps->set_cursor_begin = NULL;
	termcaps->new_term.c_iflag = 0;
	termcaps->new_term.c_oflag = 0;
	termcaps->new_term.c_cflag = 0;
	termcaps->new_term.c_lflag = 0;
	termcaps->new_term.c_line = '\0';
	termcaps->new_term.c_ispeed = 0;
	termcaps->new_term.c_ospeed = 0;
}

void	init_termcaps(t_shell *shell)
{
	char	*term_type;

	termcaps_to_null(&shell->termcaps);
	if (tcgetattr(STDIN_FILENO, &shell->termcaps.old_term) == -1)
		handle_error(shell, EXIT_FAILURE);
	term_type = ft_find_value_from_key("TERM", shell->envp);
	if (!term_type)
		handle_error(shell, EXIT_FAILURE);
	if (tgetent(shell->termcaps.buffer, term_type) <= 0)
		handle_error(shell, EXIT_FAILURE);
	else if (!capabilities(&shell->termcaps))
		handle_error(shell, EXIT_FAILURE);
	free(term_type);
}

void	canonical_on(t_shell *shell)
{
	if (tcsetattr(STDIN_FILENO, TCSANOW, &shell->termcaps.old_term) == -1)
		handle_error(shell, EXIT_FAILURE);
}

void	canonical_off(t_shell *shell)
{
	shell->termcaps.new_term = shell->termcaps.old_term;
	shell->termcaps.new_term.c_lflag &= ~ICANON;
	shell->termcaps.new_term.c_iflag &= ~ECHO;
	shell->termcaps.new_term.c_lflag &= ~ISIG;
	shell->termcaps.new_term.c_lflag &= ~IEXTEN;
	shell->termcaps.new_term.c_iflag &= ~IXON;
	shell->termcaps.new_term.c_cc[VMIN] = 1;
	shell->termcaps.new_term.c_cc[VTIME] = 0;
	// shell->termcaps.new_term.c_cc[VEOF] = 1; // ^D
	shell->termcaps.new_term.c_cc[VQUIT] = 1; // ^\/
	// shell->termcaps.new_term.c_cc[VINTR] = 1; // ^C
	shell->termcaps.new_term.c_cc[VSUSP] = 1; // ^Z
	if (tcsetattr(STDIN_FILENO, TCSANOW, &shell->termcaps.new_term) == -1)
		handle_error(shell, EXIT_FAILURE);
}

// https://arcticfox1919.gitee.io/linux-manual/man-pages/man5/terminfo.5.html

int	capabilities(t_termcaps *termcaps)
{
	int	check;

	termcaps->keys_on = tgetstr("ks", &termcaps->buffer);
	if (termcaps->keys_on)
		tputs(termcaps->keys_on, 1, ft_putint);
	termcaps->keys_off = tgetstr("ke", &termcaps->buffer);
	termcaps->up_arrow = tgetstr("ku", &termcaps->buffer);
	termcaps->down_arrow = tgetstr("kd", &termcaps->buffer);
	if (IS_LINUX)
		termcaps->backspace = tgetstr("kb", &termcaps->buffer);
	else
		termcaps->backspace = ft_strdup("\x7f");
	termcaps->del_line = tgetstr("dl", &termcaps->buffer);
	termcaps->set_cursor_begin = tgetstr("cr", &termcaps->buffer);
	if (!termcaps->keys_on || !termcaps->keys_off
		|| !termcaps->up_arrow || !termcaps->down_arrow
		|| !termcaps->backspace || !termcaps->del_line
		|| !termcaps->set_cursor_begin)
		check = 0;
	else
		check = 1;
	return (check);
}

char	*ft_find_value_from_key(const char *str, char **envp)
{
	int		i;
	int		j;
	char	*ret;

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
