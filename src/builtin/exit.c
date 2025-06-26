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
 * exit — cause the shell to exit
 * The exit utility shall cause the shell to exit from its current
    execution environment with the exit status specified by the
    unsigned decimal integer n.  If the current execution environment
    is a subshell environment, the shell shall exit from the subshell
    environment with the specified exit status and continue in the
    environment from which that subshell environment was invoked;
    otherwise, the shell utility shall terminate with the specified
    exit status. If n is specified, but its value is not between 0 and
    255 inclusively, the exit status is undefined.
 */
int	builtin_exit(t_shell *shell, char **av)
{
	(void)shell;
	char *str_exit_status;
   int exit_status;

   exit_status = 0;
	if (av[1])
	{
		int i;

		i = 0;
		while (av[1][i])
		{
			if (!ft_isdigit(av[1][i])) // check numeric arg 
			{
				ft_putendl_fd("exit\nNeed numeric argument", STDERR_FILENO);	
				exit(2);
			}
			i++;
		}
		if (av[2]) // check si 1 seul arg 
				return(ft_putendl_fd("exit\nToo many arguments", STDERR_FILENO), 1);
    	exit_status = ft_atoi(av[1]);
	}
	// exit normal, recupere le dernier exit status	$?
	else
	{
		str_exit_status = recup_var(shell->cmd.envp_copy, "?", 1);
		exit_status = ft_atoi(str_exit_status);
	}
   ft_putendl_fd("exit", STDERR_FILENO);
   exit(exit_status);
}

// si exit sans arg = juste exit normal
// si arg doit etre only numeric
// donc vweerif si arg est num only sinon exit + mess d'erreur non num , avec erreur 2
// faire aussi too many arg , avec erreur 1 mais ne quitte pas 

// zero 0 succes
// 1 si erreur 
// si pb d'arg, code erreur 2 (pb d'option)