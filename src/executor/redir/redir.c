/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlichten <hlichten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 20:30:25 by hlichten          #+#    #+#             */
/*   Updated: 2025/07/07 20:30:28 by hlichten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	cleanup_redirections(t_shell *shell);

void	process_all_redirections(t_shell *shell, char **av)
{
	int	i;

	i = 0;
	shell->executor.nb_redir = 0;
	shell->executor.nb_redir_wip = 0;
	while (av && av[i])
	{
		if (is_redir(av[i]))
			shell->executor.nb_redir++;
		i++;
	}
	if (shell->executor.nb_redir > 0)
	{
		while (shell->executor.nb_redir_wip < shell->executor.nb_redir)
		{
			shell->executor.nb_redir_wip++;
			free_tab(&shell->executor.redir_av);
			set_redir_file_type_av(shell, av);
			redir_handle(shell);
		}
	}
	else
		cleanup_redirections(shell);
}

static void	cleanup_redirections(t_shell *shell)
{
	free_ptr((void **)&shell->executor.redir_file);
	shell->executor.redir_file = NULL;
	shell->executor.redir_type = 0;
	free_tab(&shell->executor.redir_av);
}

void	redir_handle(t_shell *shell)
{
	t_token_type	type;

	type = shell->executor.redir_type;
	if (shell->executor.nb_redir > 0)
	{
		if (type == T_REDIR_IN)
			handle_redir_in(shell, shell->executor.redir_file);
		if (type == T_REDIR_OUT)
			handle_redir_out(shell, shell->executor.redir_file);
		if (type == T_REDIR_APPEND)
			handle_redir_append(shell, shell->executor.redir_file);
	}
}

void	set_redir_type(t_shell *shell, char *redir)
{
	if (ft_strcmp(redir, ">") == 0)
		shell->executor.redir_type = T_REDIR_OUT;
	if (ft_strcmp(redir, ">>") == 0)
		shell->executor.redir_type = T_REDIR_APPEND;
	if (ft_strcmp(redir, "<") == 0)
		shell->executor.redir_type = T_REDIR_IN;
}
