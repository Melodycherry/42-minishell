/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlichten <hlichten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 20:33:23 by hlichten          #+#    #+#             */
/*   Updated: 2025/07/07 20:33:25 by hlichten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	error_home(t_shell *shell);
static int	execute_cd(t_shell *shell, char *path);
static void	update_pwd(t_shell *shell, char *oldpwd);

int	builtin_cd(t_shell *shell, char **av)
{
	char	*path;
	char	*home;

	if (av[1] && av[2])
	{
		ft_putendl_fd("cd: too many arguments", STDERR_FILENO);
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
	if (execute_cd(shell, path))
		return (1);
	return (0);
}

static int	error_home(t_shell *shell)
{
	(void)shell;
	ft_putendl_fd("cd: HOME not set", STDERR_FILENO);
	return (1);
}

static void	update_pwd(t_shell *shell, char *oldpwd)
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
		free_ptr((void **)&newpwd);
		unfructuous_malloc(shell);
	}
	newpwd_str = ft_strjoin("PWD=", newpwd);
	if (!newpwd_str)
	{
		free_ptr((void **)&oldpwd_str);
		free_ptr((void **)&newpwd);
		unfructuous_malloc(shell);
	}
	set_env(oldpwd_str, TO_BOTH, shell);
	set_env(newpwd_str, TO_BOTH, shell);
	free_ptr((void **)&oldpwd_str);
	free_ptr((void **)&newpwd_str);
	free_ptr((void **)&newpwd);
}

static int	execute_cd(t_shell *shell, char *path)
{
	char	*oldpwd;

	oldpwd = getcwd(NULL, 0);
	if (!oldpwd)
	{
		free_all(shell);
		exit(1);
	}
	if (chdir(path))
	{
		perror("cd");
		free_ptr((void **)&oldpwd);
		return (1);
	}
	update_pwd(shell, oldpwd);
	free_ptr((void **)&oldpwd);
	return (0);
}
