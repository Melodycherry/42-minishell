/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlichten <hlichten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 20:33:45 by hlichten          #+#    #+#             */
/*   Updated: 2025/07/07 20:33:47 by hlichten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_bool	ft_isoperator(int c)
{
	if (c == '|' || c == '>' || c == '<')
		return (TRUE);
	return (FALSE);
}

t_bool	only_quote(t_token *token, char quote)
{
	int	i;

	i = 0;
	if (token == NULL || ft_strlen(token->value) == 0)
		return (FALSE);
	while (token->value[i])
	{
		if (token->value[i] != quote && token->value[i] != ' ')
			return (FALSE);
		i++;
	}
	return (TRUE);
}

char	*error_multiple_operator(t_token *token, t_shell *shell)
{
	if (shell->tlist.token_cnt > 1)
	{
		while (token)
		{
			if (token->next)
			{
				if (token->type == 3 && token->next->type == 4)
					token = token->next;
				else if ((token->type >= 3 && token->type <= 6)
					&& (token->next->type >= 3 && token->next->type <= 6))
					return (token->value);
			}
			token = token->next;
		}
	}
	return (NULL);
}

void	extract_dbl_token(t_shell *shell, int *i, int *j, t_token *current)
{
	(*i) = (*i) + 2;
	create_insert_token(shell, *i, *j, current);
}

void	extract_sgl_token(t_shell *shell, int *i, int *j, t_token *current)
{
	(*i)++;
	create_insert_token(shell, *i, *j, current);
}
