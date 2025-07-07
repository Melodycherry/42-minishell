/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_type.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlichten <hlichten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 20:36:03 by hlichten          #+#    #+#             */
/*   Updated: 2025/07/07 20:36:06 by hlichten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	change_type_if_valid(t_shell *shell,
				t_token *token, int *i, int *j);

void	check_var_env(t_shell *shell, t_token *token)
{
	int	i;
	int	j;

	while (token)
	{
		i = 0;
		if (token->type == T_WORD)
		{
			while (token->value[i])
			{
				if (token->value[i] == '\'')
					find_next_quote('\'', token->value, &i);
				else
					change_type_if_valid(shell, token, &i, &j);
			}
		}
		token = token->next;
	}
}

static void	change_type_if_valid(t_shell *shell,
				t_token *token, int *i, int *j)
{
	while (token->value[*i] != '$' && token->value[*i])
		(*i)++;
	if (token->value[*i] == '$')
	{
		(*i)++;
		*j = *i;
		while (token->value[*i] != '$' && token->value[*i]
			&& !ft_isquote(token->value[*i])
			&& !ft_isspace(token->value[*i]))
			(*i)++;
		if (var_exist(shell->cmd.envp_copy,
				&token->value[*j], (*i - *j)) == TRUE)
		{
			token->type = T_VAR;
			return ;
		}
		else
			(*i)--;
	}
	if (token->value[*i])
		(*i)++;
}
