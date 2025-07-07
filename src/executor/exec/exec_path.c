/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlichten <hlichten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 20:31:37 by hlichten          #+#    #+#             */
/*   Updated: 2025/07/07 21:29:25 by hlichten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		create_paths(t_shell *shell, char **envp);
static t_bool	access_command_path(t_shell *shell, char *path);
static char		*right_path(t_shell *shell, char **paths, char *cmd);

void	exec_path(t_shell *shell, char *pathname, char **av)
{
	if (is_redir(av[0]))
	{
		shell->fd.saved_stdin = dup(STDIN_FILENO);
		shell->fd.saved_stdout = dup(STDOUT_FILENO);
		process_all_redirections(shell, av);
		dup_fd_stdout(shell, TRUE);
		dup_fd_stdin(shell, TRUE);
	}
	else
		exec_from_path(shell, pathname, av);
}

void	exec_from_path(t_shell *shell, char *pathname, char **av)
{
	char	*path;

	if (ft_strchr(pathname, '/'))
		path = pathname;
	else
	{
		create_paths(shell, shell->cmd.envp_exp);
		path = right_path(shell, shell->executor.paths, pathname);
	}
	if (access_command_path(shell, path) == FALSE)
		return ;
	if (path)
		exec_fork(shell, path, av);
}

static t_bool	access_command_path(t_shell *shell, char *path)
{
	struct stat	stat_buff;

	if (access(path, F_OK) != 0)
	{
		g_exit_status = 127;
		set_exit_status_env(shell, g_exit_status);
		return (error_message(shell, "Command not found"), FALSE);
	}
	if (stat(path, &stat_buff) == 0 && S_ISDIR(stat_buff.st_mode))
	{
		g_exit_status = 126;
		errno = EISDIR;
		set_exit_status_env(shell, g_exit_status);
		return (error_message(shell, "Is a directory"), FALSE);
	}
	if (access(path, X_OK) != 0)
	{
		g_exit_status = 126;
		set_exit_status_env(shell, g_exit_status);
		return (error_message(shell, "Permission denied"), FALSE);
	}
	return (TRUE);
}

static void	create_paths(t_shell *shell, char **envp)
{
	int	i;

	i = 0;
	free_tab(&shell->executor.paths);
	while (envp[i] && ft_strncmp(envp[i], "PATH=", 5) != 0)
		i++;
	if (envp[i])
		shell->executor.paths = ft_split(envp[i] + 5, ':');
	else
	{
		g_exit_status = 127;
		set_exit_status_env(shell, g_exit_status);
		return (error_message(shell, "No such file or directory"));
	}
}

static char	*right_path(t_shell *shell, char **paths, char *cmd)
{
	int		i;
	char	*path;

	i = 0;
	while (paths[i])
	{
		path = strjoin_path(shell, paths[i], cmd);
		if (access(path, F_OK) == 0)
			return (path);
		free_ptr((void **)&path);
		i++;
	}
	return (NULL);
}
