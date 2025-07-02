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

void	error_syntax_export(char *line)
{
	ft_putstr_fd("bash: export: «", STDERR_FILENO);
	ft_putstr_fd(line, STDERR_FILENO);
	ft_putstr_fd("»: not a valid identifier\n", STDERR_FILENO);
}

void	error_syntax_unset(char *line)
{
	ft_putstr_fd("bash: unset: «", STDERR_FILENO);
	ft_putstr_fd(line, STDERR_FILENO);
	ft_putstr_fd("»: not a valid identifier\n", STDERR_FILENO);
}

void	error_empty_token(t_shell *shell)
{
	ft_putendl_fd("Mettre le message d erreur sur linux, mon bash de la casa est en francais we ", STDERR_FILENO);
	free_and_reset(shell);
	shell->syntax_error = TRUE;
	return ;
}

void	error_syntax_token(t_shell *shell, char *value)
{
	ft_putstr_fd("Syntax error near unexpected token '", STDERR_FILENO);
	ft_putstr_fd(value, STDERR_FILENO);
	ft_putendl_fd("'", STDERR_FILENO);
	free_and_reset(shell);
	shell->syntax_error = TRUE;
	return ;
}
