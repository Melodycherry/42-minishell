/*******************************************************************************/
/*                                                                             */
/*                                                                             */
/*                                                                             */
/*                                                                             */
/*      LES CODEUSES DU DIMANCHE                                               */
/*      FONT UN MINISHELL                                                      */
/*                                                                             */
/*                                                                             */
/*                                                                             */
/*******************************************************************************/

#include "minishell.h"

/** 
 * pwd – return working directory name
 * The pwd utility writes the absolute pathname of the current working directory to the
    standard output.
 */
void	builtin_pwd(void)
{
	// if (!)
	//		return (erreur)
	// getcwd ( a checker, exist deja )
	// getcdw( NULL, 0)
	// on print 
	// penser a free car pwd malloc !
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		perror("pwd");
		return;
	}
	ft_printf("%s\n", cwd);
	free(cwd);
}
