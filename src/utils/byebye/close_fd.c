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

t_bool	close_fd(int *fd)
{
	if (*fd != -1)
	{
		if (close(*fd) < 0)
			return (FALSE);
		*fd = -1;
	}
	return (TRUE);
}
