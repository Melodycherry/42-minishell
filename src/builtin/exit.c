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

static int	validate_exit_arg(char **av, int *exit_status);
// ML modif 
int	builtin_exit(t_shell *shell, char **av)
{
	int		exit_status;
	char	*str_exit_status;

	exit_status = 0;
	if (av[1])
		validate_exit_arg(av, &exit_status);
	else
	{
		str_exit_status = recup_var(shell->cmd.envp_copy, "?", 1);
		exit_status = ft_atoi(str_exit_status);
	}
	ft_putendl_fd("exit", STDERR_FILENO);
	free_all(shell);
	exit(exit_status);
}
// ML modif 
static int	validate_exit_arg(char **av, int *exit_status)
{
	int	i;

	i = 0;
	while (av[1][i])
	{
		if (!ft_isdigit(av[1][i]))
		{
			ft_putendl_fd("exit\nNeed numeric argument", STDERR_FILENO);
			*exit_status = 2;
			return(2);
		}
		i++;
	}
	if (av[2])
	{
		ft_putendl_fd("exit\nToo many arguments", STDERR_FILENO);
		*exit_status = 1;
		return (1);
	}
	*exit_status = ft_atoi(av[1]);
	return (0);
}
