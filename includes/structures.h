/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dareias- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 19:56:38 by dareias-          #+#    #+#             */
/*   Updated: 2021/12/06 16:03:12 by dareias-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H

typedef struct	s_tok
{
	char *value;
	enum
	{
		TOK_WORD,
		TOK_DOLLAR,
		TOK_LT,
		TOK_GT,
		TOK_ARROW_RIGHT,
		TOK_ARROW_LEFT,
		TOK_OPTION,
		TOK_S_QUOTE,
		TOK_D_QUOTE,
		TOK_SEMI,
		TOK_COLLON,
		TOK_DOT,
		TOK_EQUALS,
		TOK_BSLASH,
		TOK_OPAREN,
		TOK_CPAREN,
		TOK_SPACE,
		TOK_PIPE,
		TOK_EOL

	} e_type;

}				t_tok;

typedef struct s_lex
{
	int i;
	char c;
	char *src;
	int size;
}			t_lex;

typedef struct s_par
{
	t_lex *lex;
	t_tok *tok;
}			t_par;

typedef struct s_ast t_ast;

typedef struct s_ast
{
	enum
	{
		AST_ROOT,
		AST_COMPOUND,
		AST_VARIABLE,
		AST_VAR_DEF,
		AST_COMMAND,
		AST_COMM_ARGS,
		AST_WORD,
		AST_NULL
	} e_type;

	t_ast **branches;
	t_tok *my_tok;
	
}			t_ast;

typedef struct s_comm
{
	enum
	{
		VAR_DEF,
		COMMAND
	} e_type;

	char	*infile;
	char	*outfile;
	int		in;
	int		out;

	char	*cmd;
	char	**args;

	int		piping; // If its 0 then we are not piping 1->getting piped 2->piping someone 3->both

	int		fd_p[2]; // Pipe I'm reading from
	int		fd_n[2]; // Pipe I'm writing to;
}			t_comm;

typedef struct	s_shell
{
	char	**envp;
	char	*line;

	t_comm	**commands; // table of all cmommands

}			t_shell;

#endif
