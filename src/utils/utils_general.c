/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_general.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlichten <hlichten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 20:40:32 by hlichten          #+#    #+#             */
/*   Updated: 2025/07/07 21:31:37 by hlichten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_bool	edgecase(t_shell *shell)
{
	if (only_quote(shell->tlist.head, '"'))
	{
		set_exit_status_env(shell, 127);
		return (error_message(shell, "command not found"), TRUE);
	}
	if (only_quote(shell->tlist.head, '\''))
	{
		set_exit_status_env(shell, 127);
		return (error_message(shell, "command not found"), TRUE);
	}
	if (strcmp(shell->tlist.head->value, ".") == 0)
	{
		set_exit_status_env(shell, 2);
		return (error_message(shell, ".: filename argument required"), TRUE);
	}
	if (strcmp(shell->tlist.head->value, "..") == 0)
	{
		set_exit_status_env(shell, 127);
		return (error_message(shell, "..: command not found"), TRUE);
	}
	return (FALSE);
}

int	is_line_empty(char *line)
{
	while (*line)
	{
		if (!ft_isspace(*line))
			return (0);
		line++;
	}
	return (1);
}
