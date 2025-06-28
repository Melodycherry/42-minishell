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
	ft_putstr_fd("bash: export: «", 2);
	ft_putstr_fd(line, 2);
	ft_putstr_fd("»: not a valid identifier\n", 2);
}

void	error_syntax_unset(char *line)
{
	ft_putstr_fd("bash: unset: «", 2);
	ft_putstr_fd(line, 2);
	ft_putstr_fd("»: not a valid identifier\n", 2);
}
