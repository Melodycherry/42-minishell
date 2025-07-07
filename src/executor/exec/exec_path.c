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

static void	create_paths(t_shell *shell, char **envp);
static char	*strjoin_path(t_shell *shell, char *s1, char *s2);
static t_bool access_command_path(t_shell *shell, char *path);
static char	*right_path(t_shell *shell, char **paths, char *cmd);

void	exec_path(t_shell *shell, char *pathname, char **av) 
{
	char	*path;

	if (is_redir(av[0]))
	{
		shell->executor.is_redir_beg = TRUE;
		shell->fd.saved_stdin = dup(STDIN_FILENO);
		shell->fd.saved_stdout = dup(STDOUT_FILENO);
		process_all_redirections(shell, av);
		dup_fd_stdout(shell, TRUE);
		dup_fd_stdin(shell, TRUE);
		free_ptr((void **)&path);
	}
	else
		exec_from_path(shell, pathname, av);
}

void	exec_from_path(t_shell *shell, char *pathname, char **av)
{
	char	*path;
	t_bool	need_free = FALSE;

	if (ft_strchr(pathname, '/'))
		path = pathname;
	else
	{
		create_paths(shell, shell->cmd.envp_exp);
		if (!shell->executor.paths)
			return;
		path = right_path(shell, shell->executor.paths, pathname);
		need_free = TRUE;
	}
	if (access_command_path(shell, path) == FALSE)
	{
		if (need_free)
			free_ptr((void **)&path);
		return;
	}
	if (path)
	{
		exec_fork(shell, path, av);
		if (need_free)
			free_ptr((void **)&path);
	}
}

static t_bool access_command_path(t_shell *shell, char *path)
{
	struct stat stat_buff;

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

static char	*strjoin_path(t_shell *shell, char *s1, char *s2)
{
	char	*dest;
	char	*tmp;

	(void)shell;
	tmp = ft_strjoin(s1, "/");
	if (!tmp)
		unfructuous_malloc(shell);
	dest = ft_strjoin(tmp, s2);
	free_ptr((void **)&tmp);
	return (dest);
}

			// if (access(path, X_OK) == 0)
			// 	return (path);
			// else
			// {
			// 	ft_putendl_fd("Permission denied", STDERR_FILENO);
			// 	free_ptr((void **)&path);
			// 	return (NULL);
			// }


// static char	*right_path(t_shell *shell, char **paths, char *cmd)
// {
// 	int		i;
// 	char	*path;

// 	i = 0;
// 	if (!paths) // ajout de verif ? si unset 
// 	// 	return (NULL);
// 	while (paths[i])
// 	{
// 		path = strjoin_path(shell, paths[i], cmd);
// 		if (!access(path, F_OK))
// 		{
// 			if (!access(path, X_OK))
// 				return (path);
// 			else
// 			{
// 				ft_putendl_fd("Permission denied", STDERR_FILENO);
// 				free_ptr((void **)&path);
// 				return (NULL);
// 			}
// 		}
// 		free_ptr((void **)&path);
// 		i++;
// 	}
// 	return (NULL);
// }



// void	exec_path(t_shell *shell, char *pathname, char **av) 
// {
// 	char	*path;

// 	//printf("av0 : %s\n", shell->executor.redir_av[0]);
// 			puts("0");
// 	if (is_redir(av[0]))
// 	{
// 		puts("1");
// 		shell->fd.saved_stdin = dup(STDIN_FILENO);
// 		shell->fd.saved_stdout = dup(STDOUT_FILENO);
// 		process_all_redirections(shell, av, TRUE);
// 		exec_fork(shell, shell->executor.redir_av[0], shell->executor.redir_av);
// 		dup_fd_stdout(shell, TRUE);
// 		dup_fd_stdin(shell, TRUE);
// 		free_ptr((void **)&path);
// 	}
// 	exec_from_path(shell, pathname, av);
// }


// t_bool	access_command_path(t_shell *shell, char *path)
// {
// 	struct stat	stat_buff;

// 	if (access(path, F_OK) != 0);
// 	{
// 		g_exit_status = 127;
// 		return (error_message(shell, "command not found"), FALSE);
// 	}

// 	if(stat(path, &stat_buff) == 0 && )




// 	if (access(path, F_OK) != 0);
// 	{
// 		g_exit_status = 127;
// 		return (error_message(shell, "command not found"), FALSE);
// 	}

// }