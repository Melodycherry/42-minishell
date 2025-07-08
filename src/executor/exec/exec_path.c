/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlichten <hlichten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 20:31:37 by hlichten          #+#    #+#             */
/*   Updated: 2025/07/08 18:05:32 by hlichten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		exec_from_path(t_shell *shell, char *pathname, char **av);
static void		create_paths(t_shell *shell, char **envp);
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

static void	exec_from_path(t_shell *shell, char *pathname, char **av)
{
	char	*path;
	t_bool	is_abs;

	is_abs = FALSE;
	if (ft_strchr(pathname, '/'))
	{
		is_abs = TRUE;
		path = ft_strdup(pathname);
		if (!path)
			unfructuous_malloc(shell);
	}
	else
	{
		create_paths(shell, shell->cmd.envp_exp);
		path = right_path(shell, shell->executor.paths, pathname);
	}
	exec_path_valid(shell, path, av, is_abs);
}

t_bool	access_command_path(t_shell *shell, char *path, t_bool is_abs)
{
	struct stat	stat_buff;

	if (access(path, F_OK) != 0)
	{
		g_exit_status = 127;
		set_exit_status_env(shell, g_exit_status);
		if (is_abs == TRUE)
			return (error_message(shell, "no such file or directory"), FALSE);
		else
			return (error_message(shell, "command not found"), FALSE);
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
	{
		shell->executor.paths = ft_split(envp[i] + 5, ':');
		if (!shell->executor.paths)
			unfructuous_malloc(shell);
	}
	else
		return ;
}

static char	*right_path(t_shell *shell, char **paths, char *cmd)
{
	int		i;
	char	*path;

	i = 0;
	if (!paths)
		return (NULL);
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
