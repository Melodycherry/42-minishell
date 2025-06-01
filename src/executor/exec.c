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


// fonction de gestion de l execution
// ****** en cours ***********
void	execution(t_shell *shell)
{
	create_av(shell, shell->tlist.head);
	//if (shell->executor.av[0] == builtin); // WIP BY MELO
	
	// else // WIP BY GIGI

	if (is_absolative(shell->executor.av[0]))
	{
		execve(shell->executor.av[0], shell->executor.av, shell->cmd.envp_exp);
		printf("that s absolative\n");
	}
	else 
	{
		if (execve(shell->executor.av[0], shell->executor.av, shell->cmd.envp_exp))
			perror(NULL);
		//execve : prend : pathname, **av, **envp

	}
}

// fonction qui va checker si le path existe via le access sur le while du pathS
// ***** en cours *****
char	*right_path(char **paths, char *cmd)
{
	int i;
	char *path;
	
	i = 0;
	while (paths[i])
	{
		// path = strcat de path[i] + cmd 
		// access(path f_ok)
		// ok mais mtn on peut l executer ? (path)
	}

	return (path);
}

// focntion qui va checker l existance d un / pour determiner si c est absolative (absolu ou relative)
// faire les gestion des  edges cases de type juste des.. ou juste des / ou what // faire jour de la correction loool
// ******* a tester ***********
t_bool	is_absolative(char *str)
{
	if (ft_strchr(str, "/"))
		return (TRUE);
	return (FALSE);
}

