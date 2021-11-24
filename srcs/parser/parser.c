/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dareias- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 18:38:45 by dareias-          #+#    #+#             */
/*   Updated: 2021/11/24 13:49:39 by dareias-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 *
 * Notes: Remenber edge case where a command begins with a special char < (or similar)
 * 
*/


/*static int cmd_ammount(char *line);

int parse_line(t_shell *shell)
{
	int i;
	int c;
	int x;

	i = 0;
	c = 0;

	if (!shell->line)
		return (0);
	shell->commands = malloc(sizeof(t_comm *) * (cmd_ammount(shell->line) + 1));
	if (!shell->commands)
		return (0);

	while (shell->line[i] != '\0')
	{
		// First we initialize a command;
		shell->commands[c] = malloc(sizeof(t_comm));
		if (!shell->commands[c])
			return (0);

		
		// Run until '<', '>', '<<', '>>' or '|'
		x = i; // Store i
		while (!is_spec(shell->line[i]))
			i++;
		if (i != 0)
			i--;
		
		// Store the str in a t_comm
		shell->commands[c]->cmd = ft_substr(shell->line, x, i - x);
		c++;
	}
	shell->commands[c] = NULL;
	return (1);
}


static int cmd_ammount(char *line)
{
	int i;
	int in_cmd;
	int count;

	i = 0;
	in_cmd = 1;
	count = 1;
	while (line[i] != '\0')
	{
		if (is_spec(line[i]))
		{
			if (!in_cmd)
				in_cmd = 1;
			else
				in_cmd = 0;
			if (in_cmd)
				count++;
		}
		i++;
	}
	return (i);
}*/

void print_ast(t_ast *ast, int l);
int parse_line(t_shell *shell)
{
	t_lex *lex;
	t_par *par;
	t_ast *root;

	lex = init_lexer(shell->line);
	if (!lex)
		return (1);
	par = init_parser(lex);
	if (!par)
		return (1);
	root = parse_to_ast(par);
	print_ast(root, 0);
	if (!root)
		return (1);
	return (0);
}

void print_ast(t_ast *ast, int l)
{
	int i;
	int c;

	i = 0;
	c = 0;
	if (ast == NULL)
		return ;
	l++;
	while (c < l)
	{
		printf("-");
		c++;
	}
	printf("AST %s\n", ast_to_str(ast->e_type));
	if (ast->my_tok != NULL)
		printf("AST: Type: %s my_tok->e_type: %s my_tok: %s \n", ast_to_str(ast->e_type), tok_to_str(ast->my_tok->e_type), ast->my_tok->value);
	while (ast->branches && ast->branches[i] != NULL)
	{
		print_ast(ast->branches[i++], l);
	}
}
