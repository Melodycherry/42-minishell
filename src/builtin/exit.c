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

static void	validate_exit_arg(char **av, char *exit_status);

int	builtin_exit(t_shell *shell, char **av)
{
	int		i;
	int		exit_status;
	char	*str_exit_status;

	exit_status = 0;
	if (av[1])
		validate_exit_arg(av, exit_status);
	else
	{
		str_exit_status = recup_var(shell->cmd.envp_copy, "?", 1);
		exit_status = ft_atoi(str_exit_status);
	}
	ft_putendl_fd("exit", STDERR_FILENO);
	exit(exit_status);
}

static void	validate_exit_arg(char **av, char *exit_status)
{
	int	i;

	i = 0;
	while (av[1][i])
	{
		if (!ft_isdigit(av[1][i]))
		{
			// gestion erreur
			ft_putendl_fd("exit\nNeed numeric argument", STDERR_FILENO);
			exit(2);
		}
		i++;
	}
	if (av[2]) // gestion erreur
		return (ft_putendl_fd("exit\nToo many arguments", STDERR_FILENO), 1);
	exit_status = ft_atoi(av[1]);
}

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
