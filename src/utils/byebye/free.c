/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlichten <hlichten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 20:34:24 by hlichten          #+#    #+#             */
/*   Updated: 2025/07/07 22:21:30 by hlichten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_all(t_shell *shell)
{
	free_ptr((void **)&shell->cmd.line);
	rl_clear_history();
	free_tab(&shell->cmd.envp_copy);
	free_tab(&shell->cmd.envp_exp);
	free_tab(&shell->executor.av);
	free_tab(&shell->executor.paths);
	free_tab(&shell->executor.pipe_av);
	free_tab(&shell->executor.redir_av);
	free_ptr((void **)&shell->executor.redir_file);
	free_token_list(shell);
}

void	free_all_minus_av(t_shell *shell)
{
	free_ptr((void **)&shell->cmd.line);
	rl_clear_history();
	free_tab(&shell->cmd.envp_copy);
	free_tab(&shell->cmd.envp_exp);
	free_tab(&shell->executor.paths);
	free_tab(&shell->executor.pipe_av);
	free_tab(&shell->executor.redir_av);
	free_ptr((void **)&shell->executor.redir_file);
	free_token_list(shell);
}

void	free_and_reset(t_shell *shell)
{
	shell->executor.index_file_heredoc = 0;
	free_tab(&shell->executor.av);
	free_tab(&shell->executor.paths);
	free_tab(&shell->executor.pipe_av);
	free_tab(&shell->executor.redir_av);
	free_ptr((void **)&shell->cmd.line);
	free_ptr((void **)&shell->executor.redir_file);
	free_token_list(shell);
	shell->executor.is_forked = FALSE;
	shell->executor.end = 0;
	shell->executor.start = 0;
}

void	unfructuous_malloc(t_shell *shell)
{
	ft_putstr_fd("minishell: Cannot allocate memory", STDERR_FILENO);
	free_all(shell);
	exit(EXIT_FAILURE);
}

void	*free_ptr(void **ptr)
{
	if (*ptr && ptr)
	{
		free(*ptr);
		*ptr = NULL;
	}
	return (NULL);
}
