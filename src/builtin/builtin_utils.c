/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlichten <hlichten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 20:33:28 by hlichten          #+#    #+#             */
/*   Updated: 2025/07/07 20:33:32 by hlichten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

int	exec_builtin(t_shell *shell, t_bool is_pipe)
{
	char	**av;

	if (!shell || !shell->executor.av)
		return (1);
	if (shell->executor.redir_av)
		av = shell->executor.redir_av;
	else if (!is_pipe)
		av = shell->executor.av;
	else
		av = shell->executor.pipe_av;
	if (ft_strcmp(av[0], "cd") == 0)
		return (builtin_cd(shell, av));
	else if (ft_strncmp(av[0], "echo", 4) == 0)
		return (builtin_echo(shell, av, is_pipe));
	else if (ft_strncmp(av[0], "env", 3) == 0)
		return (builtin_env(shell, av));
	else if (ft_strcmp(av[0], "exit") == 0)
		return (builtin_exit(shell, av));
	else if (ft_strcmp(av[0], "export") == 0)
		return (builtin_export(shell, av));
	else if (ft_strcmp(av[0], "pwd") == 0)
		return (builtin_pwd(shell, av));
	else if (ft_strcmp(av[0], "unset") == 0)
		return (builtin_unset(shell, av));
	return (0);
}
