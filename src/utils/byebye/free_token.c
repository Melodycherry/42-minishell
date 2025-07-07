/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlichten <hlichten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 20:34:20 by hlichten          #+#    #+#             */
/*   Updated: 2025/07/07 21:21:22 by hlichten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_mid_list(t_token *current);

void	free_token_list(t_shell *shell)
{
	t_token	*current;
	t_token	*next;

	if (!shell)
		return ;
	current = shell->tlist.head;
	while (current)
	{
		next = current->next;
		free_ptr((void **)&current->value);
		free_ptr((void **)&current->var_value);
		free(current);
		current = NULL;
		current = next;
	}
	shell->tlist.head = NULL;
}

t_token	*handle_free_mid_list(t_token *current)
{
	t_token	*next;
	t_token	*prev;

	if (current->next && current->prev)
	{
		next = current->next;
		prev = current->prev;
		next->prev = prev;
		prev->next = next;
	}
	if (!current->next && current->prev)
	{
		next = NULL;
		prev = current->prev;
		prev->next = NULL;
	}
	if (current->next && !current->prev)
	{
		next = current->next;
		next->prev = NULL;
	}
	if (!current->next && !current->prev)
		return (NULL);
	free_mid_list(current);
	return (next);
}

static void	free_mid_list(t_token *current)
{
	free_ptr((void **)&current->value);
	free(current);
}
