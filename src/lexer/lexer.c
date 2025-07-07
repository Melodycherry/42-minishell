/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlichten <hlichten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 20:33:39 by hlichten          #+#    #+#             */
/*   Updated: 2025/07/07 20:33:42 by hlichten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	skip_spaces(char *line, int i);
static int	handle_quote(t_shell *shell, char *line, int i);

void	token_blank(t_shell *shell)
{
	int		i;
	int		j;
	char	*line;
	t_token	*token;

	i = 0;
	line = shell->cmd.line;
	if (!line)
		return ;
	while (line[i])
	{
		i = skip_spaces(line, i);
		j = i;
		while (line[i] && !ft_isspace(line[i]))
			i = handle_quote(shell, line, i);
		if (i > j)
		{
			token = create_token(shell, T_UNKNOWN, &line[j], (i - j));
			insert_base_list(&shell->tlist, token);
		}
	}
}

static int	skip_spaces(char *line, int i)
{
	while (line[i] && ft_isspace(line[i]))
		i++;
	return (i);
}

static int	handle_quote(t_shell *shell, char *line, int i)
{
	if (((line[i]) == '\'' || line[i] == '"')
		&& is_next_quote(shell, line[i], line, i) == TRUE)
		find_next_quote(line[i], line, &i);
	else
		while (line[i] && !ft_isspace(line[i]) && !ft_isquote(line[i]))
			i++;
	return (i);
}
