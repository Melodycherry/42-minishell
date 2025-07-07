/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlichten <hlichten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 20:36:18 by hlichten          #+#    #+#             */
/*   Updated: 2025/07/07 20:36:20 by hlichten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	expansion(t_shell *shell)
{
	t_token	*token;

	token = shell->tlist.head;
	check_var_env(shell, shell->tlist.head);
	while (token)
	{
		if (token->type == T_VAR)
		{
			expand_var(shell, token);
			if (is_quote_string(token->value))
				delete_quotes_value(shell, token);
		}
		if (token->type == T_WORD)
		{
			if (is_quote_string(token->value))
				delete_quotes_value(shell, token);
		}
		token = token->next;
	}
}

void	expand_var(t_shell *shell, t_token *token)
{
	int		i;
	int		j;
	char	*value;

	value = token->value;
	i = 0;
	j = 0;
	while (value[i])
	{
		if (value[i] == '"')
			expand_double_quote(shell, token, &i, &j);
		else if (value [i] == '\'')
			expand_single_quote(shell, token, &i, &j);
		else if (value[i] == '$')
			expand_dollar(shell, token, &i, &j);
		else
			i++;
	}
	if (i > j)
		token->var_value
			= join_free(shell, token->var_value, &value[j], (i - j));
}
