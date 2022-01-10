/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jibanez- <jibanez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 19:56:38 by dareias-          #+#    #+#             */
/*   Updated: 2022/01/10 17:52:20 by dareias-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H

typedef struct s_shell t_shell;
typedef struct s_tok
{
	char	*value;
	enum
	{
		TOK_WORD,
		TOK_DOLLAR,
		TOK_LT,
		TOK_GT,
		TOK_ARROW_RIGHT,
		TOK_ARROW_LEFT,
		TOK_OPTION,
		TOK_TILDE,
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
		TOK_ERROR,
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
		AST_VAR_EXP,
		AST_COMMAND,
		AST_COMM_ARGS,
		AST_REDIRECT,
		AST_DELIMITER,
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
		COMMAND,
		INVALID
	} e_type;

	char	*infile;
	char	*outfile;
	char	*heredoc;
	int		in;
	int		out;
	int		redir;

	char	*cmd;
	char	**args;

	t_shell *shell;
	// Should the two bellow be deleted
	//char	**envp;
	//char	**vars;

	int		piping; // If its 0 then we are not piping 1->getting piped 2->piping someone 3->both

	int		fd_p[2]; // Pipe I'm reading from (previous)
	int		fd_n[2]; // Pipe I'm writing to (next)

	int		is_ft;
}			t_comm;

typedef struct s_termcaps
{
	struct termios	old_term;
	struct termios	new_term;
	char			*buffer;
	char			*keys_on;
	char			*keys_off;
	char			*up_arrow;
	char			*down_arrow;
	char			*backspace;
	char			*del_line;
	char			*set_cursor_begin;
}				t_termcaps;

typedef struct	s_shell
{
	char		**envp;
	char		*line;
	int			*debug;
	char		**vars;
	char		**exports; // The idea is to keep track of what we store in envp to know if it's up to us to free
	int			exit_status; // Terminal can exit with some status, so if we start a bash in our bash (inception) we can know what was the exit from the second bash
	struct		sigaction sa;
	t_termcaps	termcaps;
	t_comm		**commands; // table of all commands

}			t_shell;


#endif
