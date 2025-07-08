/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlichten <hlichten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 20:35:58 by hlichten          #+#    #+#             */
/*   Updated: 2025/07/08 17:50:28 by hlichten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	reset_index(int *i, int*j);

void	expand_single_quote(t_shell *shell, t_token *token, int *i, int *j)
{
	char	*value;

	value = token->value;
	if (*i > *j)
		token->var_value
			= join_free(shell, token->var_value, &value[*j], (*i - *j));
	(*i)++;
	(*j) = (*i);
	while (value[*i] && value[*i] != '\'')
	{
		while (value[*i] && value[*i] != '\'')
			(*i)++;
		if (*i > *j)
		{
			token->var_value
				= join_free(shell, token->var_value, &value[*j], (*i - *j));
			(*j) = (*i);
		}
	}
	if (value[*i])
		reset_index(i, j);
}

void	expand_double_quote(t_shell *shell, t_token *token, int *i, int *j)
{
	char	*value;

	value = token->value;
	if (*i > *j)
		token->var_value
			= join_free(shell, token->var_value, &value[*j], (*i - *j));
	(*i)++;
	(*j) = (*i);
	while (value[*i] && value[*i] != '"')
	{
		while (value[*i] && value[*i] != '$' && value[*i] != '"')
			(*i)++;
		if (*i > *j)
		{
			token->var_value
				= join_free(shell, token->var_value, &value[*j], (*i - *j));
			(*j) = (*i);
		}
		if (value[*i] == '$')
			expand_dollar(shell, token, i, j);
	}
	if (value[*i])
		reset_index(i, j);
}

void	expand_dollar(t_shell *shell, t_token *token, int *i, int *j)
{
	char	*value;
	char	*rec_var;

	value = token->value;
	if (*i > *j)
		token->var_value = join_free(shell, token->var_value, &value[*j],
				(*i - *j));
	if (value[*i] == '\0')
		return ;
	reset_index(i, j);
	while (value[*i] && value[*i] != '$' && !ft_isquote(value[*i])
		&& !ft_isspace(value[*i]))
		(*i)++;
	if (*i > *j && var_exist(shell->cmd.envp_copy, &value[*j], (*i - *j)))
	{
		rec_var = recup_var(shell->cmd.envp_copy, &value[*j], (*i - *j));
		token->var_value = join_free(shell, token->var_value, rec_var,
				get_segment_len(rec_var));
		(*j) = (*i);
	}
	if (value[*i])
		reset_index(i, j);
}

static void	reset_index(int *i, int*j)
{
	(*i)++;
	*j = *i;
}
