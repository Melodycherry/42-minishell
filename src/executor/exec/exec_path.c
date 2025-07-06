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

static void	create_path(t_shell *shell, char **envp);
static char	*strjoin_path(t_shell *shell, char *s1, char *s2);
static char	*right_path(t_shell *shell, char **paths, char *cmd);

void	exec_path(t_shell *shell, char *pathname, char **av)
{
	char	*path;

	if (ft_strchr(pathname, '/'))
		exec_fork(shell, pathname, av);
	else
	{
		create_path(shell, shell->cmd.envp_exp);
		path = right_path(shell, shell->executor.paths, pathname);
		if (path)
		{
			exec_fork(shell, path, av);
			free_ptr((void **)&path);
		}
	}
}

static void	create_path(t_shell *shell, char **envp)
{
	int	i;

	i = 0;
	while (envp[i] && ft_strncmp(envp[i], "PATH=", 5) != 0)
		i++;
	if (envp[i] && envp[i][5]) // check pour unset path 
		shell->executor.paths = ft_split(envp[i] + 5, ':');
	else
		shell->executor.paths = NULL;
}

static char	*right_path(t_shell *shell, char **paths, char *cmd)
{
	int		i;
	char	*path;

	i = 0;
	if (!paths) // ajout de verif ? si unset 
		return (NULL);
	while (paths[i])
	{
		path = strjoin_path(shell, paths[i], cmd);
		if (!access(path, F_OK))
		{
			if (!access(path, X_OK))
				return (path);
			else
			{
				ft_putendl_fd("Permission denied", STDERR_FILENO);
				free_ptr((void **)&path);
				return (NULL);
			}
		}
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
