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
