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

// a voir comment mettre ca en place mais ca peut etre cool d avoir diff fonctions de checking d errreur qui se retrouvent ici
// int		check_error(t_shell *shell)
// {
// 	if (check_quotes(shell) == 1)
// 		return (EXIT_FAILURE); // il faut modif ici pour reprompt minishell ? 
// 	return(0);
// }

void    error_syntax_export(char *line)
{
    ft_putstr_fd("bash: export: «", 2);
    ft_putstr_fd(line, 2);
    ft_putstr_fd("»: not a valid identifier", 2);
}

void    error_syntax_unset(char *line)
{
    ft_putstr_fd("bash: unset: «", 2);
    ft_putstr_fd(line, 2);
    ft_putstr_fd("»: not a valid identifier", 2);
}