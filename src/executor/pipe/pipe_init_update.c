/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_init_update.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlichten <hlichten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 20:31:10 by hlichten          #+#    #+#             */
/*   Updated: 2025/07/07 20:31:12 by hlichten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_pipe_av(t_shell *shell)
{
	shell->executor.start = 0;
	shell->executor.end = 0;
}

void	update_executor_state(t_shell *shell)
{
	free_tab(&shell->executor.pipe_av);
	shell->executor.end++;
	shell->executor.start = shell->executor.end;
}

void	update_parent_fds(t_shell *shell, int nb_pipe)
{
	if (shell->fd.prev_fd != -1)
		close_fd(&shell->fd.prev_fd);
	if (nb_pipe > 0)
	{
		close_fd(&shell->fd.fd_pipe[1]);
		shell->fd.prev_fd = shell->fd.fd_pipe[0];
	}
	else
		close_fd(&shell->fd.prev_fd);
}
