/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaning.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dareias- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 19:48:24 by dareias-          #+#    #+#             */
/*   Updated: 2021/11/26 13:27:27 by dareias-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLEANING_H
# define CLEANING_H

int clean_shell(t_shell *shell);
int	clean_ast(t_ast *ast);
int clean_parser(t_par *par);
int clean_lexer(t_lex *lex);
int clean_tok(t_tok *tok);

#endif
