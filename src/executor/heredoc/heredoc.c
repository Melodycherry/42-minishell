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

static void	update_type_heredoc_eof_for_exec(t_token *token, char *file);

void	handle_heredoc(t_shell *shell)
{
	t_token	*current;
	char	*file;

	current = shell->tlist.head;
	update_type_eof(shell->tlist.head);
	nb_heredoc(shell, shell->tlist.head);
	while (current->next)
	{
		if (current->type == T_HEREDOC)
		{
			shell->executor.index_file_heredoc++;
			file = generate_file(shell, current);
			update_type_heredoc_eof_for_exec(current, file);
		}
		current = current->next;
	}
}

static void	update_type_heredoc_eof_for_exec(t_token *token, char *file)
{
	token->type = T_REDIR_IN;
	free (token->value);
	token->value = ft_strdup("<");
	if (token->next)
	{
		token->next->type = T_WORD;
		free(token->next->value);
		token->next->value = ft_strdup(file);
	}
}

void	update_type_eof(t_token *token)
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
					delete_quotes_value(token->next);
				}
			}
			else
				perror("pas de delimiteur faire gestion d erreur"); // faire un puthandle shit
		}
		token = token->next;
	}
}
