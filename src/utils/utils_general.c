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

t_bool	edgecase(t_shell *shell)
{
	if (only_quote(shell->tlist.head, '"'))
	{
		set_exit_status_env(shell, 127);
		return (error_message(shell, "command ' ' not found"), TRUE);
	}
	if (only_quote(shell->tlist.head, '\''))
	{
		set_exit_status_env(shell, 127);
		return (error_message(shell, "command ' ' not found"), TRUE);
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

	// if (shell->tlist.head->type == T_REDIR_APPEND
	// 	|| shell->tlist.head->type == T_REDIR_OUT
	// 	|| shell->tlist.head->type == T_REDIR_IN)
	// {
	// 	set_exit_status_env(shell, 2);
	// 	return (error_message(shell, "command expected before redirection"));
	// }