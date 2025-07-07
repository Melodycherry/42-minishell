/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlichten <hlichten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 20:33:35 by hlichten          #+#    #+#             */
/*   Updated: 2025/07/07 20:33:37 by hlichten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_bool	ft_isquote(int c)
{
	if ((c == '\'' || c == '"'))
		return (TRUE);
	return (FALSE);
}

t_bool	is_next_quote(t_shell *shell, char quote, char *line, int i)
{
	i++;
	while (line[i] && line[i] != quote)
		i++;
	if (line[i] == '\0')
	{
		ft_putstr_fd("syntax error : quote expected. ", STDERR_FILENO);
		ft_putendl_fd("Minishell does not handle that", STDERR_FILENO);
		free_all(shell);
		exit(EXIT_FAILURE);
	}
	if (line [i] == quote)
		return (TRUE);
	return (FALSE);
}

void	find_next_quote(char quote, char *line, int *i)
{
	(*i)++;
	while (line[*i] && line[*i] != quote)
		(*i)++;
	(*i)++;
}
