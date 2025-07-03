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

	printf("exec_pipe called in pid %d\n", getpid());
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
	char	**pipe_av;

	pipe_av = split_args(shell, shell->executor.av);
	if (nb_pipe > 0)
		create_pipe_or_exit(shell, fd_pipe);
	else
	{
		fd_pipe[0] = -1;
		fd_pipe[1] = -1;
	}
	// shell->executor.prev_fd = *prev_fd;
	pid = fork_process_or_exit(shell);
	printf("forked pid: %d (parent: %d)\n", pid, getpid());
	if (pid == 0)
	{
		child_signal();
		check_fd(shell, *prev_fd);
		exec_pipe_child(shell, fd_pipe, pipe_av, nb_pipe);
	}
	update_parent_fds(prev_fd, fd_pipe, nb_pipe);
	update_executor_state(shell, pipe_av);
	return (pid);
}

void	exec_pipe_child(t_shell *shell, int *fd_pipe, char **pipe_av,
	int nb_pipe)
{
	// if (shell->executor.nb_pipe != nb_pipe) 
	// {
    //     handle_dup2(shell, shell->executor.prev_fd, STDIN_FILENO);
    //     close(shell->executor.prev_fd);
    // }
	if (nb_pipe > 0)
	{
		close(fd_pipe[0]);
		handle_dup2(shell, fd_pipe[1], STDOUT_FILENO);
		close(fd_pipe[1]);
	}
	exec_path(shell, pipe_av[0], pipe_av);
	free_tab(&pipe_av);
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
