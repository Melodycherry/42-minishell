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
void	builtin_pwd(t_shell *shell)
{
	(void)shell;
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		perror("pwd");
		return;
	}
	printf("%s\n", cwd);
	free(cwd);
}