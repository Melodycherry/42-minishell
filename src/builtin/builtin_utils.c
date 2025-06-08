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

#include "minishell.h"

t_bool	is_builtin(char	*cmd)
{
	// verif s'il y a une commande ?	
	if (!cmd)
		return FALSE; // ou retourne erreur ? 
	// check si on trouve un builtin
	if ( ft_strcmp(cmd, "echo") == 0
		|| ft_strcmp(cmd, "cd") == 0
		|| ft_strcmp(cmd, "env") == 0
		|| ft_strcmp(cmd, "exit") == 0
		|| ft_strcmp(cmd, "export") == 0
		|| ft_strcmp(cmd, "pwd") == 0
		|| ft_strcmp(cmd, "unset") == 0)
		return TRUE;
	return FALSE;
}
// fonction d'excecution des builtin **WIP**
void	exec_builtin(t_shell *shell)
{
	char	**av;

	if (!shell || !shell->executor.av)
		return;
	av = shell->executor.av;
	// verif si pas null ? 
	if (!av || !av[0])
		return;
	// check pour chaque builtin
	// if (ft_strcmp(av[0], "cd") == 0)
	// 	return (builtin_cd(shell));
	else if (ft_strcmp(av[0], "echo") == 0)
		return (builtin_echo(shell));
	else if (ft_strcmp(av[0], "env") == 0)
		return (builtin_env(shell));
	// else if (ft_strcmp(av[0], "exit") == 0)
	// 	return (builtin_exit());
	else if (ft_strcmp(av[0], "export") == 0)
		return (handle_export(shell, shell->tlist.head));
	else if (ft_strcmp(av[0], "pwd") == 0)
		return (builtin_pwd(shell));
	// else if (ft_strcmp(av[0], "unset") == 0)
	// 	return (builtin_unset());
}