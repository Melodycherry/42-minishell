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

static int	error_home(t_shell *shell);
static void	execute_cd(t_shell *shell, char *path);
static void	update_pwd(t_shell *shell, char *oldpwd);

int	builtin_cd(t_shell *shell, char **av)
{
	char	*path;
	char	*home;

	if (av[1] && av[2])
	{
		ft_putendl_fd("cd: too many arguments", STDERR_FILENO); // TODO: Free des trucs ici ?? pour chaque erreur ??
		return (1);
	}
	if (av[1] && av[1][0] == '-')
	{
		ft_putendl_fd("Invalid option", STDERR_FILENO);
		return (2);
	}
	if (!av[1])
	{
		home = recup_var(shell->cmd.envp_copy, "HOME", ft_strlen("HOME"));
		if (!home)
			error_home(shell);
		path = home;
	}
	else
		path = av[1];
	execute_cd(shell, path);
	return (0);
}

static int	error_home(t_shell *shell)
{
	(void)shell;
	ft_putendl_fd("cd: HOME not set", STDERR_FILENO);
	return (1);
}

static void	update_pwd(t_shell *shell, char *oldpwd) //TODO: REFFACTO
{
	char	*newpwd;
	char	*oldpwd_str;
	char	*newpwd_str;

	newpwd = getcwd(NULL, 0);
	if (!newpwd)
		unfructuous_malloc(shell);
	oldpwd_str = ft_strjoin("OLDPWD=", oldpwd);
	if (!oldpwd_str)
	{
		free_ptr((void**)&newpwd);
		unfructuous_malloc(shell);
	}
	newpwd_str = ft_strjoin("PWD=", newpwd);
	if (!newpwd_str)
	{
		free_ptr((void**)&oldpwd_str);
		free_ptr((void**)&newpwd);
		unfructuous_malloc(shell);
	}
	if (oldpwd_str && newpwd_str)
	{
		set_env(oldpwd_str, TO_BOTH, shell);
		set_env(newpwd_str, TO_BOTH, shell);
	}
	free_ptr((void **)&oldpwd_str);
	free_ptr((void **)&newpwd_str);
	free_ptr((void **)&newpwd);
}

static void	execute_cd(t_shell *shell, char *path)
{
	char	*oldpwd;

	oldpwd = getcwd(NULL, 0);
	if (!oldpwd)
		return ;
	if (chdir(path) == -1)
	{
		perror("cd");
		free_ptr((void **)&oldpwd);
		return ;
	}
	update_pwd(shell, oldpwd);
	free_ptr((void **)&oldpwd);
}
