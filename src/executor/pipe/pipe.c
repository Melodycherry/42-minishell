/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlichten <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 20:30:58 by hlichten          #+#    #+#             */
/*   Updated: 2025/07/08 01:18:48 by hlichten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static pid_t	exec_pipe_iteration(t_shell *shell, int nb_pipe);
static void		exec_pipe_child(t_shell *shell, int nb_pipe);

void	exec_pipe(t_shell *shell)
{
	pid_t	pid;
	int		nb_pipe;

	init_pipe_av(shell);
	nb_pipe = shell->executor.nb_pipe;
	while (nb_pipe >= 0)
	{
		pid = exec_pipe_iteration(shell, nb_pipe);
		nb_pipe--;
	}
	if (shell->fd.prev_fd != -1)
		close_fd(&shell->fd.prev_fd);
	wait_for_all(shell, pid);
	parent_signal();
}

static pid_t	exec_pipe_iteration(t_shell *shell, int nb_pipe)
{
	pid_t	pid;

	shell->executor.pipe_av = split_args(shell, shell->executor.av);
	if (nb_pipe > 0)
		create_pipe_or_exit(shell);
	pid = fork_process_or_exit(shell);
	sig_core_dump_parent_signal();
	if (pid == 0)
	{
		shell->executor.is_forked = TRUE;
		child_signal();
		dup_fd_stdin(shell, FALSE);
		exec_pipe_child(shell, nb_pipe);
	}
	update_parent_fds(shell, nb_pipe);
	update_executor_state(shell);
	return (pid);
}

static void	exec_pipe_child(t_shell *shell, int nb_pipe)
{
	int		exit_status;

	exit_status = 1;
	if (nb_pipe > 0)
	{
		close_fd(&shell->fd.fd_pipe[0]);
		dup_fd_stdout(shell, FALSE);
	}
	if (is_builtin(shell->executor.pipe_av[0]))
	{
		shell->fd.saved_stdin = dup(STDIN_FILENO);
		shell->fd.saved_stdout = dup(STDOUT_FILENO);
		process_all_redirections(shell, shell->executor.pipe_av);
		exit_status = exec_builtin(shell, TRUE);
		dup_fd_stdin(shell, TRUE);
		dup_fd_stdout(shell, TRUE);
		free_tab(&shell->executor.redir_av);
	}
	else
		exec_path(shell, shell->executor.pipe_av[0], shell->executor.pipe_av);
	free_tab(&shell->executor.pipe_av);
	free_all(shell);
	exit(exit_status);
}

void	wait_for_all(t_shell *shell, pid_t last_pid)
{
	int		stat_loc;
	int		exit_status;
	pid_t	pid;

	exit_status = 0;
	while (1)
	{
		pid = wait(&stat_loc);
		if (pid <= 0)
			break ;
		if (pid == last_pid)
		{
			if (WIFEXITED(stat_loc))
				exit_status = WEXITSTATUS(stat_loc);
			else if (WIFSIGNALED(stat_loc))
				exit_status = 128 + WTERMSIG(stat_loc);
			else
				exit_status = EXIT_FAILURE;
			set_exit_status_env(shell, exit_status);
		}
	}
}
