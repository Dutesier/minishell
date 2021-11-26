/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dareias- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 19:50:03 by dareias-          #+#    #+#             */
/*   Updated: 2021/11/26 17:52:55 by dareias-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

int		parse_line(t_shell *shell);
t_tok	*init_token(char *value, int type);
t_lex *init_lexer(char *src);
void lex_next(t_lex *lex);
t_tok *lex_get_word(t_lex *lex);
t_tok *next_token(t_lex *lex);
t_tok *token_switch(char c, t_lex *lex);
t_tok *token_switch_two(char c, t_lex *lex);
t_tok *token_switch_three(t_lex *lex);
t_tok *lex_get_space(t_lex *lex);
//t_tok *lex_get_optn(t_lex *lex);
t_ast *init_ast(int type);
void ast_add_branch(t_ast *parent, t_ast *child, int i);
int ast_branch_ammount(t_ast *ast);
t_par *init_parser(t_lex *lex);
t_tok *parser_next(t_par *par, unsigned int type);
t_ast *parse_to_ast(t_par *par);
t_ast *parse_word(t_par *par);
t_ast* parse_variable(t_par *par);
t_ast *parse_compound(t_par *par);
t_ast *parse_command(t_par *par);
int is_compound(t_par *par);
int	nextquote(t_lex *lex, int q);

#endif
