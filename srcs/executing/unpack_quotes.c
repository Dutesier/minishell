/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unpack_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jibanez- <jibanez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 16:03:09 by dareias-          #+#    #+#             */
/*   Updated: 2022/03/09 16:39:24 by jibanez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	unpack_quotes(t_shell *shell, t_ast *ast)
{
	int	i;
	int	ret;

	i = 0;
	ret = 0;
	while (ast && ast->branches && ast->branches[i] != NULL)
	{
		unpack_quotes(shell, ast->branches[i]);
		if (ast->branches[i]->my_tok
			&& ast->branches[i]->my_tok->e_type == TOK_DQUOTED)
			ret += expand_quote(shell, ast, i);
		i++;
	}
	return (ret);
}

int	expand_quote(t_shell *shell, t_ast *father, int i)
{
	int		j;
	int		found_dollar;
	t_ast	*son;
	char	*value;

	j = 0;
	found_dollar = 0;
	son = father->branches[i];
	value = son->my_tok->value;
	while (value[j] != '\0')
	{
		if (value[j] == '$')
		{
			found_dollar = 1;
			break ;
		}
		j++;
	}
	if (found_dollar && value[j + 1] != '\"' && value[j + 1] != ' ')
		return (exp_needed(shell, father,
				ft_dupnoq(father->branches[i]->my_tok->value), i));
	return (no_exp_needed(son, value));
}

// exp stands for expansion

int	no_exp_needed(t_ast *son, char *value)
{
	t_tok	*temp;

	temp = init_token(value, TOK_WORD);
	clean_tok(son->my_tok);
	son->my_tok = temp;
	return (1);
}

int	exp_needed(t_shell *shell, t_ast *father, char *og_str, int dqindex)
{
	char	*new_str;
	char	*variable_expanded;
	int		i;
	int		x;
	int		j;

	i = 0;
	x = 0;
	variable_expanded = getvar_from_dq(shell, og_str);
	if (!variable_expanded)
		variable_expanded = ft_strdup("");
	j = dq_expanded_len(og_str) + ft_strlen(variable_expanded);
	new_str = malloc(sizeof(char) * (j + 1));
	if (!new_str)
		return (0);
	while (og_str[i++] != '\0')
	{
		if (og_str[i] == '$')
			break ;
		new_str[i] = og_str[i];
	}
	j = i;
	while (og_str[i] != '\0' && og_str[i] != ' ')
		i++;
	while (variable_expanded[x] != '\0')
		new_str[j++] = variable_expanded[x++];
	while (og_str[i] != '\0')
		new_str[j++] = og_str[i++];
	new_str[j] = '\0';
	free(variable_expanded);
	free(og_str);
	return (no_exp_needed(father->branches[dqindex], new_str));
}

char	*getvar_from_dq(t_shell *shell, char *str)
{
	int		i;
	int		len;
	char	*var;
	char	*ret;

	i = 0;
	len = 0;
	while (str[i++] != '\0')
	{
		if (str[i] == '$')
			break ;
	}
	if (str[i] == '\0')
		return (NULL);
	while (str[i + len++] != '\0')
	{
		if (str[i + len] == ' ')
			break ;
	}
	if (str[i + len] != '\0')
		len = len - 1;
	var = ft_substr(str, i + 1, len);
	ret = ft_variable(shell, var);
	free(var);
	return (ret);
}
