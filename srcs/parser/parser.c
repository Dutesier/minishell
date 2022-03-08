/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dareias- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 18:38:45 by dareias-          #+#    #+#             */
/*   Updated: 2022/03/07 23:30:25 by dareias-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 *
 * Notes: Remenber edge case where a command begins with a special char < (or similar)
 * 
*/


int parse_line(t_shell *shell)
{
	t_lex	*lex;
	t_par	*par;
	t_ast	*root;

	handle_expansion(shell);
	//shell->line = ft_dupnoq(shell->line);
	lex = init_lexer(shell->line);
	if (!lex)
		return (1);
	par = init_parser(lex);
	if (!par)
		return (1);
	root = parse_to_ast(par);
	if (!root)
		return (1);
	//command_ammount(root, 0);
	if (shell->debug)
	{
		printf("************* DEBUGGING *************\n");
		printf("\n%s", ft_color(PUR));
		print_ast(root, 0);
		printf("%s\n", ft_color(WHT));
	}
	ast_handler(shell, root);
	shell->line = par->lex->src; //Because of get quote we might need to repoint shell.line to the actual line
	//printf("Calling clean ast from parse line\n");
	clean_ast(root);
	clean_parser(par);
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
		printf("- ");
		c++;
	}
	printf("[%s]", ast_to_str(ast->e_type));
	if (ast->my_tok != NULL)
	{
		printf(": (%s) :  ->%s<- \n", tok_to_str(ast->my_tok->e_type), ast->my_tok->value);
	}
	if (!ast->my_tok)
		printf("\n");
	while (ast->branches && ast->branches[i] != NULL)
	{
		print_ast(ast->branches[i++], l);
	}
}

void	update_next(t_par *par, unsigned int *next)
{
	*next = par->tok->e_type;
}