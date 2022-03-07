/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jibanez- <jibanez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 14:51:49 by dareias-          #+#    #+#             */
/*   Updated: 2022/03/01 14:39:49 by jibanez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * Four main steps:
 * 1 - Initialize the program
 * 2 - Read and parse the command given
 * 3 - Execute given command
 * 4 - Clean and exit
 *
 * Steps 2 & 3 run on a loop
 *
*/

int	main(int argc, char *argv[], char **envp)
{
	t_shell	shell;

	init_shell(&shell, envp);
	
	// FOR TESTING ONLY
	// argv[2] will contains the content of the line for example "echo something ; ls -la"
	if (argc >= 3 && !ft_strcmp(argv[1], "-c", 3))
	{
		int exit_status = interactive_mode(&shell, argv);
		exit(exit_status);
	}
    // Above this is the function that normally launch your minishell, instead
    // of reading line with a get_next_line or a read() on fd 0, you just have to get
    // the argv[2] (which contains the content) and execute it.
    // Your function should return the good exit status otherwise the tests may be considered as false.

	if (argc > 1 && ft_strcmp(argv[1], "-debug", ft_min(ft_strlen(argv[1]), 6)))
		shell.debug = 1;
	else if (argc > 1)
		return (interactive_mode(&shell, argv));
	shell.loop = 1;
	while (shell.loop)
	{
		// canonical_off(&shell);
		signal(SIGINT, handle_sig);
		signal(SIGQUIT, SIG_IGN);
		get_line(&shell);
		if (shell.line != NULL)
		{
			parse_line(&shell);
			clean_shell(&shell);
		}
		// canonical_on(&shell);
	}
	if (shell.vars)
		clean_vars(&shell);
	if (shell.envp)
		clean_envp(&shell);
	clear_history();
	return (EXIT_SUCCESS);
}
