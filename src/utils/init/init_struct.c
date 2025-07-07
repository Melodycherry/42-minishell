/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlichten <hlichten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 20:34:45 by hlichten          #+#    #+#             */
/*   Updated: 2025/07/07 22:21:16 by hlichten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	init_list(t_shell *shell);
static void	init_executor(t_shell *shell);

void	init_all(t_shell *shell)
{
	init_list(shell);
	init_executor(shell);
	shell->cmd.envp_copy = NULL;
	shell->cmd.envp_exp = NULL;
	shell->cmd.line = NULL;
	shell->syntax_error = FALSE;
	shell->lexer.space = 0;
	shell->lexer.double_quote = 0;
	shell->lexer.single_quote = 0;
	shell->fd.fd_pipe[0] = -1;
	shell->fd.fd_pipe[1] = -1;
	shell->fd.prev_fd = -1;
	shell->fd.saved_stdin = -1;
	shell->fd.saved_stdout = -1;
	shell->fd.fd_heredoc = -1;
}

static void	init_list(t_shell *shell)
{
	shell->tlist.head = NULL;
	shell->tlist.token_cnt = 0;
}

static void	init_executor(t_shell *shell)
{
	shell->executor.end = 0;
	shell->executor.start = 0;
	shell->executor.nb_pipe = 0;
	shell->executor.nb_redir = 0;
	shell->executor.redir_type = 0;
	shell->executor.nb_heredoc = 0;
	shell->executor.nb_redir_wip = 0;
	shell->executor.index_file_heredoc = 0;
	shell->executor.av = NULL;
	shell->executor.paths = NULL;
	shell->executor.pipe_av = NULL;
	shell->executor.redir_av = NULL;
	shell->executor.redir_file = NULL;
	shell->executor.is_forked = FALSE;
	shell->executor.is_redir_beg = FALSE;
}
