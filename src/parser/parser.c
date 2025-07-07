/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlichten <hlichten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 20:33:50 by hlichten          #+#    #+#             */
/*   Updated: 2025/07/07 20:33:52 by hlichten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	skip_non_operator(char *value, int i);
static int	process_operator(t_shell *shell, t_token *current, int *i, int *j);

void	token_operator(t_shell *shell, t_token *current)
{
	int		i;
	int		j;
	int		check;

	while (current)
	{
		i = 0;
		j = 0;
		check = process_operator(shell, current, &i, &j);
		if (check > 0)
		{
			if (i > j)
				create_insert_token(shell, i, j, current);
			current = handle_free_mid_list(current);
			shell->tlist.token_cnt--;
			if (current)
				current = current->prev;
		}
		if (current)
			current = current->next;
		else
			current = NULL;
	}
}

static int	process_operator(t_shell *shell, t_token *current, int *i, int *j)
{
	int		check;
	char	*value;

	check = 0;
	value = current->value;
	while (value[*i])
	{
		*i = skip_non_operator(value, *i);
		if (ft_isquote(value[*i]))
			find_next_quote(value[*i], value, i);
		if (ft_isoperator(value[*i]))
		{
			check++;
			if (*i > *j)
				create_insert_token(shell, *i, *j, current);
			insert_operator(shell, i, j, current);
			*j = *i;
		}
	}
	return (check);
}

static int	skip_non_operator(char *value, int i)
{
	while (!ft_isquote(value[i]) && !ft_isoperator(value[i]) && value[i])
		i++;
	return (i);
}

void	insert_operator(t_shell *shell, int *i, int *j, t_token *current)
{
	char	*value;

	value = current->value;
	(*j) = (*i);
	if (value[*i + 1] == '>' && value[*i] == '>')
		extract_dbl_token(shell, i, j, current);
	else if (value[*i + 1] == '<' && value[*i] == '<')
		extract_dbl_token(shell, i, j, current);
	else
		extract_sgl_token(shell, i, j, current);
}

void	token_typedef(t_token *token)
{
	while (token)
	{
		if (token->value[0] == '|')
			token->type = T_PIPE;
		else if (token->value[0] == '>' && token->value[1] == '>')
			token->type = T_REDIR_APPEND;
		else if (token->value[0] == '<' && token->value[1] == '<')
			token->type = T_HEREDOC;
		else if (token->value[0] == '>')
			token->type = T_REDIR_OUT;
		else if (token->value[0] == '<')
			token->type = T_REDIR_IN;
		else
			token->type = T_WORD;
		token = token->next;
	}
}
