/**
 * @brief Finds the executable path for a given command.
 *
 * This function determines whether the given command is an absolute/relative
 * path or needs to be searched in the PATH environment variable. It delegates
 * the appropriate logic to helper functions and returns the resolved path or
 * an error message.
 *
 * @param shell Pointer to the shell structure.
 * @param cmd The command to resolve.
 * @param exit_status Pointer to the exit status to update in case of errors.
 * @return The resolved path of the command if found, or an error message.
 */
char	*find_path_cmd(t_shell *shell, char *cmd, int *exit_status)
{
	if (ft_strcmp(cmd, ".") == 0)
	{
		*exit_status = OP_ERROR;
		return (cmd_filename_arg(shell));
	}
	if (ft_strcmp(cmd, "..") == 0)
		return (cmd_not_found(shell, cmd));
	if (ft_strchr(cmd, '/'))
		return (handle_absolute_path(shell, cmd, exit_status));
	return (search_in_path(shell, cmd));
}

/**
 * @brief Handles commands with absolute or relative paths.
 *
 * This function checks if the given command exists, is executable, and is not
 * a directory. If any of these checks fail, an appropriate error message is
 * returned. If the command is valid, a duplicate of the command path is
 * returned.
 *
 * @param shell Pointer to the shell structure.
 * @param cmd The command to check.
 * @param exit_status Pointer to the exit status to update in case of errors.
 * @return A duplicate of the command path if valid, or an error message.
 */
static char	*handle_absolute_path(t_shell	*shell, char *cmd, int *exit_status)
{
	struct stat	sb;
	char		*dup_cmd;

	if (access(cmd, F_OK) == S_ERROR)
	{
		*exit_status = CMD_NOT_FND;
		return (cmd_exec_error(shell, cmd));
	}



	if (stat(cmd, &sb) == S_SUCCESS && S_ISDIR(sb.st_mode))
	{
		*exit_status = CMD_NOT_EXEC;
		errno = EISDIR;
		return (cmd_exec_error(shell, cmd));
	}



	if (access(cmd, X_OK) == S_ERROR)
	{
		*exit_status = CMD_NOT_EXEC;
		return (cmd_exec_error(shell, cmd));
	}


	
	dup_cmd = ft_strdup(cmd);
	if (!dup_cmd)
		exit_and_handle_msg(shell, MALLOC_ERROR_EXE_CMD, EXIT_FAILURE);
	return (dup_cmd);
}

/**
 * @brief Searches for a command in the PATH environment variable.
 *
 * This function retrieves the PATH environment variable, splits it into
 * directories, and searches for the given command in each directory. If the
 * command is found, its full path is returned. If not, an error message is
 * returned.
 *
 * @param shell Pointer to the shell structure.
 * @param cmd The command to search for.
 * @param exit_status Pointer to the exit status to update in case of errors.
 * @return The full path of the command if found, or an error message.
 */
static char	*search_in_path(t_shell *shell, char *cmd)
{
	char		**paths;
	char		*envp_path;

	envp_path = ft_getenv(shell, "PATH");
	if (!envp_path)
		return (cmd_not_found(shell, cmd));
	paths = ft_split(envp_path, ':');
	if (!paths)
		exit_and_handle_msg(shell, MALLOC_ERROR_EXE_CMD, EXIT_FAILURE);
	return (get_path_cmd(shell, paths, cmd));
}

/**
 * @brief Retrieves the full path of a command from a list of directories.
 *
 * This function iterates through the directories in the PATH environment
 * variable, appends the command name to each directory, and checks if the
 * resulting path is executable. If a valid path is found, it is returned.
 *
 * @param shell Pointer to the shell structure.
 * @param paths Array of directories from the PATH environment variable.
 * @param cmd The command to search for.
 * @return The full path of the command if found, or an error message.
 */
static char	*get_path_cmd(t_shell *shell, char **paths, char *cmd)
{
	int		i;
	char	*path;

	i = 0;
	while (paths[i])
	{
		path = ft_strdup(paths[i]);
		if (!path
			|| !safe_str_append(&path, "/")
			|| !safe_str_append(&path, cmd))
		{
			free_ptr((void **) &path);
			free_char_tab(paths);
			exit_and_handle_msg(shell, MALLOC_ERROR_EXE_CMD, EXIT_FAILURE);
		}
		if (access(path, F_OK | X_OK) == 0)
		{
			free_char_tab(paths);
			return (path);
		}
		free_ptr((void **) &path);
		i++;
	}
	free_char_tab(paths);
	return (cmd_not_found(shell, cmd));
}
