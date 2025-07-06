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

void	edgecase(t_shell *shell)
{
	if (only_quote(shell->tlist.head, '"'))
	{
		set_exit_status_env(shell, 127);
		return (error_message(shell, "command ' ' not found"));
	}
	if (only_quote(shell->tlist.head, '\''))
	{
		set_exit_status_env(shell, 127);
		return (error_message(shell, "command ' ' not found"));
	}
	if (strcmp(shell->tlist.head->value, ".") == 0)
	{
		set_exit_status_env(shell, 2);
		return (error_message(shell, ".: filename argument required"));
	}
	if (strcmp(shell->tlist.head->value, "..") == 0)
	{
		set_exit_status_env(shell, 127);
		return (error_message(shell, "..: command not found"));
	}
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
