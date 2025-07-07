/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_expand.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlichten <hlichten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 20:30:11 by hlichten          #+#    #+#             */
/*   Updated: 2025/07/07 20:30:18 by hlichten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_bool	is_dollar_present(char *line);
static char		*heredoc_expansion(t_shell *shell, char *line);
static char		*expand_var_segment(t_shell *shell, char *line, int *i, int *j);

char	*expand_all_vars_in_heredoc(t_shell *shell, char *line)
{
	char	*tmp;

	tmp = NULL;
	if (is_dollar_present(line) == TRUE)
		tmp = heredoc_expansion(shell, line);
	else
	{
		tmp = ft_strdup(line);
		if (!tmp)
			unfructuous_malloc(shell);
	}
	return (tmp);
}

static t_bool	is_dollar_present(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '$')
			return (TRUE);
		i++;
	}
	return (FALSE);
}

static char	*heredoc_expansion(t_shell *shell, char *line)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	j = 0;
	while (line[i])
	{
		if (line[i] == '$')
		{
			tmp = expand_var_segment(shell, line, &i, &j);
		}
		else
			i++;
	}
	if (i > j)
		tmp = join_free(shell, tmp, &line[j], i - j);
	return (tmp);
}

static char	*expand_var_segment(t_shell *shell, char *line, int *i, int *j)
{
	char	*tmp;
	char	*rec_var;

	tmp = NULL;
	if (*i > *j)
		tmp = join_free(shell, tmp, &line[*j], *i - *j);
	(*i)++;
	*j = *i;
	while (line[*i] && (ft_isalnum(line[*i])
			|| line[*i] == '$' || line[*i] == '_'))
		(*i)++;
	if (*i > *j && var_exist(shell->cmd.envp_copy, &line[*j], *i - *j))
	{
		rec_var = recup_var(shell->cmd.envp_copy, &line[*j], *i - *j);
		tmp = join_free(shell, tmp, rec_var, ft_strlen(rec_var));
	}
	else
		tmp = join_free(shell, tmp, &line[*j], *i - *j);
	*j = *i;
	return (tmp);
}
