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
int		check_error(t_shell *shell)
{
	if (check_quotes(shell) == 1)
		return (EXIT_FAILURE); // il faut modif ici pour reprompt minishell ? 
	return(0);
}