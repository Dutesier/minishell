// Lets build all the redirections before we run the commands

int setup_redirs(t_shell *shell, t_ast *root. int comm_ammount)
{
	int *redir_table;
	int	i;
	int z;

	i = 0;
	z = 0;
	redir_table = malloc(sizeof(int) * ((comm_ammount * 2) + 1));
	if (!redir_table)
		return (1);
	redir_table[comm_ammount] = -42;
	while (shell->commands[i] != NULL)
	{
		shell->commands[i]->in = get_commands_input(shell->commands, root, i);
		shell->commands[i]->out = get_commands_output(shell->commands, root, i);
		redir_table[z++] = shell->commands[i]->in;
		redir_table[z++] = shell->commands[i]->out;
		i++;
	}
	if (comm_ammount != z)
		ft_putstr_fd(2, "Command ammount is different from ammount of redirections set\n");
	return (0);
}
