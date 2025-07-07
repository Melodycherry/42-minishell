/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_chain.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlichten <hlichten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 20:34:33 by hlichten          #+#    #+#             */
/*   Updated: 2025/07/07 20:34:37 by hlichten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	insert_mid_list(t_token *current,
				t_token *new_token, t_shell *shell);

void	create_insert_token(t_shell *shell, int i, int j, t_token *current)
{
	t_token	*new_token;
	char	*value;

	value = current->value;
	current->var_value = NULL;
	new_token = create_token(shell, T_UNKNOWN, &value[j], i - j);
	insert_mid_list(current, new_token, shell);
	shell->tlist.token_cnt++;
}

t_token	*create_token(t_shell *shell, int type, char *value, int n)
{
	t_token	*new_token;

	(void)shell;
	new_token = malloc(sizeof(t_token));
	if (!new_token)
		unfructuous_malloc(shell);
	ft_memset(new_token, 0, sizeof(t_token));
	new_token->value = ft_strndup(value, n);
	if (!new_token->value)
	{
		free(new_token);
		unfructuous_malloc(shell);
	}
	new_token->type = type;
	return (new_token);
}

void	insert_base_list(t_tlist *tlist, t_token *token)
{
	t_token	*current;

	if (!tlist || !token)
		return ;
	if (!tlist->head)
	{
		tlist->head = token;
		token->next = NULL;
		token->prev = NULL;
		tlist->token_cnt = 1;
	}
	else
	{
		current = tlist->head;
		while (current->next)
			current = current->next;
		current->next = token;
		token->prev = current;
		token->next = NULL;
		tlist->token_cnt++;
	}
}

static void	insert_mid_list(t_token *current,
			t_token *new_token, t_shell *shell)
{
	t_token	*prev;

	if (!new_token || !current)
		return ;
	if (current->prev == NULL)
	{
		new_token->prev = NULL;
		shell->tlist.head = new_token;
	}
	else
	{
		prev = current->prev;
		new_token->prev = prev;
		prev->next = new_token;
	}
	new_token->next = current;
	current->prev = new_token;
	if (shell->tlist.head == current)
		new_token = shell->tlist.head;
}
