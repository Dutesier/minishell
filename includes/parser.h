/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dareias- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 19:50:03 by dareias-          #+#    #+#             */
/*   Updated: 2021/11/19 19:44:41 by dareias-         ###   ########.fr       */
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
t_tok *lex_get_optn(t_lex *lex);

#endif
