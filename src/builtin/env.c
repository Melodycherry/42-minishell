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
 * Executes the builtin env command: Prints the environment variables.
 */
int	builtin_env(t_shell *shell, char **av)
{
	if (!*shell->cmd.envp_copy)
	{
		printf("no env bitch\n");
		return(0);
	}
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
	print_tab(shell->cmd.envp_copy);
	return (0);
}
//fonction de test pour voir si la copie du tableau s est bien faite.
void	print_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab && tab[i])
	{
		printf("%s\n", tab[i]);
		i++;
	}
}