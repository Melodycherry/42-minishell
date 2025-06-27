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

/* 
 * Executes the builtin env command: Prints the environment variables.
*/

static void	print_tab_env(char **tab);

int	builtin_env(t_shell *shell, char **av)
{
	if (!*shell->cmd.envp_copy)
	{
		printf("no env bitch\n");
		return (0);
	}
	if (av[1] && av[1][0] == '-')
	{
		ft_putendl_fd("Invalid option", STDERR_FILENO);
		return (2);
	}
	if (av[1])
	{
		ft_putendl_fd("Too many arguments", STDERR_FILENO);
		return (1);
	}
	print_tab_env(shell->cmd.envp_copy);
	return (0);
}

static void	print_tab_env(char **tab)
{
	int	i;

	i = 1;
	while (tab && tab[i])
	{
		printf("%s\n", tab[i]);
		i++;
	}
}
