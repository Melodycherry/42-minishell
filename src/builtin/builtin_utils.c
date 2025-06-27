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

t_bool	is_builtin(char	*cmd)
{
	if (!cmd)
		return (FALSE);
	if (ft_strcmp(cmd, "echo") == 0
		|| ft_strcmp(cmd, "cd") == 0
		|| ft_strcmp(cmd, "env") == 0
		|| ft_strcmp(cmd, "exit") == 0
		|| ft_strcmp(cmd, "export") == 0
		|| ft_strcmp(cmd, "pwd") == 0
		|| ft_strcmp(cmd, "unset") == 0)
		return (TRUE);
	return (FALSE);
}

int	exec_builtin(t_shell *shell)
{
	char	**av;

	if (!shell || !shell->executor.av)
		return (1);
	if (shell->executor.redir_av)
		av = shell->executor.redir_av;
	else
		av = shell->executor.av;
	if (ft_strcmp(av[0], "cd") == 0)
		return (builtin_cd(shell, shell->executor.av));
	else if (ft_strcmp(av[0], "echo") == 0)
		return (builtin_echo(shell, shell->executor.av));
	else if (ft_strcmp(av[0], "env") == 0)
		return (builtin_env(shell, shell->executor.av));
	else if (ft_strcmp(av[0], "exit") == 0)
		return (builtin_exit(shell, shell->executor.av));
	else if (ft_strcmp(av[0], "export") == 0)
		return (builtin_export(shell, shell->executor.av));
	else if (ft_strcmp(av[0], "pwd") == 0)
		return (builtin_pwd(shell, shell->executor.av));
	else if (ft_strcmp(av[0], "unset") == 0)
		return (builtin_unset(shell, shell->executor.av));
	return (0);
}
