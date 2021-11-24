/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dareias- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 16:24:46 by dareias-          #+#    #+#             */
/*   Updated: 2021/11/24 13:48:59 by dareias-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

typedef enum e_exit_code
{
	MEMORY_FAIL,
	FILE_OPEN_FAIL,
	FORK_FAIL,
	EXEC_FAIL
}			t_exit_code;

// Strings
char	**ft_split(char const *s, char c);
int		ft_strcmp(char *str1, char *str2, int cmp);
int		ft_strlen(char *str);
char	*ft_append(char *str, char *append);
char	*ft_strdup(char *s);
char	*ft_strjoin(char *s1, char *s2);
int		ft_strchr(char c, char *s);
char	*ft_substr(char *str, int start, int ammount);

// Error printing
int		print_error(int error);
int		ft_putstr_fd(char *s, int fd);
char *tok_to_str(unsigned int type);
char *ast_to_str(unsigned int type);

// Pattern matching
int		is_spec(char c);
int		ft_isalpha(int c);
int		ft_isdigit(int c);
int		ft_isalnum(int c);
int		ft_isspace(int c);

#endif
