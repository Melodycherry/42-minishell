/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlichten <hlichten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 20:34:40 by hlichten          #+#    #+#             */
/*   Updated: 2025/07/07 20:34:42 by hlichten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	create_fake_env(t_shell *shell);
static void	create_fake_exp(t_shell *shell);
static void	increase_shlvl_env(t_shell *shell);
static void	increase_shlvl_exp(t_shell *shell);

void	cpy_envp(t_shell *shell, char **envp)
{
	if (!envp || *envp == NULL)
	{
		create_fake_env(shell);
		create_fake_exp(shell);
	}
	else
	{
		shell->cmd.envp_copy = init_envp_copy(shell, envp);
		shell->cmd.envp_exp = cpy_tab(shell, envp);
		bubble_tab(shell->cmd.envp_exp);
	}
	increase_shlvl_env(shell);
	increase_shlvl_exp(shell);
}

static void	create_fake_env(t_shell *shell)
{
	char	**tmp;

	tmp = malloc(sizeof(char *) * 4);
	if (!tmp)
		unfructuous_malloc(shell);
	tmp[0] = ft_strdup("?=0");
	tmp[1] = ft_strdup("PWD=/home/mlaffita/Documents/Minishell");
	tmp[2] = ft_strdup("SHLVL=1");
	tmp[3] = NULL;
	shell->cmd.envp_copy = tmp;
}

static void	create_fake_exp(t_shell *shell)
{
	char	**tmp;

	tmp = malloc(sizeof(char *) * 3);
	if (!tmp)
		unfructuous_malloc(shell);
	tmp[0] = ft_strdup("PWD=/home/mlaffita/Documents/Minishell");
	tmp[1] = ft_strdup("SHLVL=1");
	tmp[2] = NULL;
	shell->cmd.envp_exp = tmp;
}

static void	increase_shlvl_env(t_shell *shell)
{
	int		i;
	int		new_index;
	char	*new_index_upgraded;
	char	*old_index;

	i = 0;
	while (shell->cmd.envp_copy[i])
	{
		if (ft_strncmp(shell->cmd.envp_copy[i], "SHLVL", 5) == 0)
		{
			old_index = ft_strdup(&shell->cmd.envp_copy[i][6]);
			new_index = atoi(old_index);
			new_index++;
			new_index_upgraded = ft_itoa(new_index);
			if (!new_index_upgraded)
				unfructuous_malloc(shell);
			free_ptr((void **)&shell->cmd.envp_copy[i]);
			shell->cmd.envp_copy[i] = ft_strjoin("SHLVL=", new_index_upgraded);
			free_ptr((void **)&old_index);
			free_ptr((void **)&new_index_upgraded);
		}
		i++;
	}
}

static void	increase_shlvl_exp(t_shell *shell)
{
	int		i;
	int		new_index;
	char	*new_index_upgraded;
	char	*old_index;

	i = 0;
	while (shell->cmd.envp_exp[i])
	{
		if (ft_strncmp(shell->cmd.envp_exp[i], "SHLVL", 5) == 0)
		{
			old_index = ft_strdup(&shell->cmd.envp_exp[i][6]);
			new_index = atoi(old_index);
			new_index++;
			new_index_upgraded = ft_itoa(new_index);
			if (!new_index_upgraded)
				unfructuous_malloc(shell);
			free_ptr((void **)&shell->cmd.envp_exp[i]);
			shell->cmd.envp_exp[i] = ft_strjoin("SHLVL=", new_index_upgraded);
			free_ptr((void **)&old_index);
			free_ptr((void **)&new_index_upgraded);
		}
		i++;
	}
}
