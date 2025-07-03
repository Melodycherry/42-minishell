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

static pid_t	exec_pipe_iteration(t_shell *shell, int *prev_fd, int *fd_pipe,
					int nb_pipe);

void	exec_pipe(t_shell *shell)
{
	pid_t	pid;
	int		prev_fd;
	int		fd_pipe[2];
	int		nb_pipe;

	prev_fd = -1;
	init_pipe(shell);
	nb_pipe = shell->executor.nb_pipe;
	while (nb_pipe >= 0)
	{
		pid = exec_pipe_iteration(shell, &prev_fd, fd_pipe, nb_pipe);
		nb_pipe--;
	}
	if (prev_fd != -1)
		close(prev_fd);
	wait_for_all(shell, pid);
}

static pid_t	exec_pipe_iteration(t_shell *shell, int *prev_fd, int *fd_pipe,
		int nb_pipe)
{
	pid_t	pid;

	shell->executor.pipe_av = split_args(shell, shell->executor.av);
	if (nb_pipe > 0)
		create_pipe_or_exit(shell, fd_pipe);
	else
	{
		fd_pipe[0] = -1;
		fd_pipe[1] = -1;
	}
	pid = fork_process_or_exit(shell);
	if (pid == 0)
	{
		child_signal();
		check_fd(shell, *prev_fd);
		exec_pipe_child(shell, fd_pipe, nb_pipe);
	}
	update_parent_fds(prev_fd, fd_pipe, nb_pipe);
	update_executor_state(shell);
	return (pid);
}

void	exec_pipe_child(t_shell *shell, int *fd_pipe, int nb_pipe)
{
	int		saved_stdin;
	int		saved_stdout;
	int		exit_status;

	if (nb_pipe > 0)
	{
		close(fd_pipe[0]);
		handle_dup2(shell, fd_pipe[1], STDOUT_FILENO);
		close(fd_pipe[1]);
	}
	if (is_builtin(shell->executor.pipe_av[0]))
	{
		saved_stdin = dup(STDIN_FILENO);
		saved_stdout = dup(STDOUT_FILENO);
		set_redir_count(shell, shell->executor.pipe_av);
		exit_status = exec_builtin(shell, TRUE);
		set_exit_status_env(shell, exit_status);
		handle_dup2(shell, saved_stdin, STDIN_FILENO);
		handle_dup2(shell, saved_stdout, STDOUT_FILENO);
		close(saved_stdin);
		close(saved_stdout);
		free_tab(&shell->executor.redir_av);
	}
	else
		exec_path(shell, shell->executor.pipe_av[0], shell->executor.pipe_av);
	sleep(20);
	free_tab(&shell->executor.pipe_av);
	free_all(shell);
	exit(EXIT_FAILURE);
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
