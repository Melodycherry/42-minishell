/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlichten <hlichten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 20:31:24 by hlichten          #+#    #+#             */
/*   Updated: 2025/07/08 18:01:00 by hlichten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	convert_list_to_av(t_shell *shell, t_token *current)
{
	int		i;
	char	**av;

	i = 0;
	av = malloc(sizeof(char *) * (shell->tlist.token_cnt + 1));
	if (!av)
		unfructuous_malloc(shell);
	while (i < shell->tlist.token_cnt)
	{
		if (current->type == T_VAR)
			av[i] = ft_strdup(current->var_value);
		else
			av[i] = ft_strdup(current->value);
		if (!av[i])
			free_mid_tab(shell, &av, i);
		current = current->next;
		i++;
	}
	av[i] = NULL;
	free_tab(&shell->executor.av);
	shell->executor.av = av;
}

char	*strjoin_path(t_shell *shell, char *s1, char *s2)
{
	char	*dest;
	char	*tmp;

	(void)shell;
	tmp = ft_strjoin(s1, "/");
	if (!tmp)
		unfructuous_malloc(shell);
	dest = ft_strjoin(tmp, s2);
	if (!dest)
		unfructuous_malloc(shell);
	free_ptr((void **)&tmp);
	return (dest);
}

void	exec_path_valid(t_shell *shell, char *path, char **av, t_bool is_abs)
{
	if (!path)
	{
		error_message(shell, "command not found");
		g_exit_status = 127;
		set_exit_status_env(shell, g_exit_status);
		return ;
	}
	if (access_command_path(shell, path, is_abs) == FALSE)
	{
		free_ptr((void **)&path);
		return ;
	}
	exec_fork(shell, path, av);
}
