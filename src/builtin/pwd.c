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
int	builtin_pwd(t_shell *shell, char **av)
{
	(void)shell;
	char	*cwd;

	if (av[1] && av[1][0] == '-')
	{
		ft_putendl_fd("Invalid option", STDERR_FILENO);
		return(2);
	}
	if (av[1])
	{
		ft_putendl_fd("Too many arguments", STDERR_FILENO);
		return(1);
	}
	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		perror("pwd");
		return(1);
	}
	printf("%s\n", cwd);
	free(cwd);
	return(0);
}
