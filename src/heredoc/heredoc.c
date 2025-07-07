/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlichten <hlichten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 20:29:48 by hlichten          #+#    #+#             */
/*   Updated: 2025/07/07 20:37:36 by hlichten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	update_type_eof(t_shell *shell, t_token *token);
static char	*generate_file(t_shell *shell, t_token *token);
static char	*delete_quotes_hd(t_shell *shell, char *line);
static void	update_type_eof_exec(t_shell *shell, t_token *token, char *file);

void	handle_heredoc(t_shell *shell)
{
	t_token	*current;
	char	*file;

	current = shell->tlist.head;
	update_type_eof(shell, shell->tlist.head);
	nb_heredoc(shell, shell->tlist.head);
	while (current)
	{
		if (current->type == T_HEREDOC)
		{
			shell->executor.index_file_heredoc++;
			file = generate_file(shell, current);
			if (!file)
			{
				set_exit_status_env(shell, 2);
				return (error_message(shell, "Error: missing delimiter"));
			}
			update_type_eof_exec(shell, current, file);
			free_ptr((void **)&file);
		}
		if (current->next)
			current = current->next;
		else
			return ;
	}
}

static void	update_type_eof(t_shell *shell, t_token *token)
{
	while (token->next)
	{
		if (token->type == T_HEREDOC)
		{
			if (token->next)
			{
				token->next->type = T_EOF;
				if (is_quote_string(token->next->value) == TRUE)
				{
					token->next->type = T_EOF_Q;
					token->next->value
						= delete_quotes_hd(shell, token->next->value);
				}
			}
		}
		token = token->next;
	}
}

static char	*generate_file(t_shell *shell, t_token *token)
{
	char	*file;
	char	*eof;
	t_bool	need_exp;

	need_exp = TRUE;
	if (token->next)
	{
		eof = token->next->value;
		if (token->next->type == T_EOF_Q)
			need_exp = FALSE;
	}
	else
		return (NULL);
	file = create_name(shell);
	process_hd_file(shell, file, eof, need_exp);
	return (file);
}

static void	update_type_eof_exec(t_shell *shell, t_token *token, char *file)
{
	token->type = T_REDIR_IN;
	free_ptr((void **)&token->value);
	token->value = ft_strdup("<");
	if (token->next)
	{
		token->next->type = T_WORD;
		free_ptr((void **)&token->next->value);
		token->next->value = ft_strdup(file);
		if (!token->next->value)
			unfructuous_malloc(shell);
	}
}

static char	*delete_quotes_hd(t_shell *shell, char *line)
{
	int		i;
	int		j;
	char	*new_line;

	i = 0;
	new_line = NULL;
	while (line[i])
	{
		j = i;
		while (line[i] && !ft_isquote(line[i]))
			i++;
		if (i > j)
			new_line = join_free(shell, new_line, &line[j], (i - j));
		if (ft_isquote(line[i]))
		{
			j = i;
			find_next_quote(line[i], line, &i);
			new_line = join_free(shell, new_line, &line[j + 1], (i - j - 2));
		}
	}
	return (new_line);
}
