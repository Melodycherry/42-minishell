/*****************************************************************************/
/*                                                                           */
/*                                                                           */
/*                                                                           */
/*                                                                           */
/*      LES CODEUSES DU DIMANCHE                                             */
/*      FONT UN MINISHELL                                                    */
/*                                                                           */
/*                                                                           */
/*                                                                           */
/*****************************************************************************/

#include "minishell.h"

static void	update_type_eof(t_shell *shell, t_token *token);
static char	*generate_file(t_shell *shell, t_token *token);
static void	update_type_eof_exec(t_shell *shell, t_token *token, char *file);

void	handle_heredoc(t_shell *shell)
{
	t_token	*current;
	char	*file;

	current = shell->tlist.head;
	update_type_eof(shell, shell->tlist.head);
	nb_heredoc(shell, shell->tlist.head);
	while (current->next)
	{
		if (current->type == T_HEREDOC)
		{
			if (current->next->type != T_EOF && current->next->type != T_EOF_Q)
				return ft_putendl_fd("Syntaxe error: missing delimiter", STDERR_FILENO);
			shell->executor.index_file_heredoc++;
			file = generate_file(shell, current);
			if (!file)
				return ft_putendl_fd("Syntaxe error: missing delimiter", STDERR_FILENO);
			update_type_eof_exec(shell, current, file);
			free_ptr((void **)&file);
		}
		current = current->next;
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
	{
		ft_putendl_fd("Syntaxe error: missing delimiter", STDERR_FILENO); //on passe pas par ici ?
		return (NULL);
	}
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
					delete_quotes_value(shell, token->next);
				}
			}
			else
				ft_putendl_fd("Syntaxe error: missing delimiter",
					STDERR_FILENO);
		}
		token = token->next;
	}
}
