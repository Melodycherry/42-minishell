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
	char	**pipe_av;

	pipe_av = split_args(shell, shell->executor.av);
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

void	wait_for_all(t_shell *shell, pid_t pid)
{
	int		stat_loc;
	int		exit_status;
	char	*value;
	char	*str_exit_status;

	if (pid > 0)
		waitpid(pid, &stat_loc, 0);
	if (WIFEXITED(stat_loc) == TRUE)
		exit_status = WEXITSTATUS(stat_loc);
	else if (WIFSIGNALED(stat_loc) == TRUE)
		exit_status = 128 + WTERMSIG(stat_loc);
	else
		exit_status = EXIT_FAILURE;
	str_exit_status = ft_itoa(exit_status);
	if (!str_exit_status)
		unfructuous_malloc(shell);
	value = ft_strjoin("?=", str_exit_status);
	if (!value)
	{
		free_ptr((void **)&str_exit_status);
		unfructuous_malloc(shell);
	}
	free_ptr((void **) &str_exit_status);
	set_env(value, TO_ENV, shell);
	free_ptr((void **) &value);
}

// version avant refacto
// void exec_pipe(t_shell *shell)
// {
// 	pid_t	pid;
// 	int		prev_fd = -1;
// 	int		fd_pipe[2];
// 	int		nb_pipe;
// 	char	**pipe_av;

// 	init_pipe(shell);
// 	nb_pipe = shell->executor.nb_pipe;
// 	while (nb_pipe >= 0)
// 	{
// 		pipe_av = split_args(shell, shell->executor.av);
// 		if (nb_pipe > 0)
// 			create_pipe_or_exit(fd_pipe);
// 		else
// 		{
// 			fd_pipe[0] = -1;
// 			fd_pipe[1] = -1;
// 		}
// 		pid = fork_process_or_exit();
// 		if (pid == 0)
// 		{
// 			check_fd(prev_fd);
// 			exec_pipe_child(shell, fd_pipe, pipe_av, nb_pipe);
// 		}
// 		if (prev_fd != -1)
// 			close(prev_fd);

// 		if (nb_pipe > 0)
// 		{
// 			close(fd_pipe[1]);
// 			prev_fd = fd_pipe[0];
// 		}
// 		else
// 			prev_fd = -1;

// 		update_executor_state(shell, pipe_av);
// 		nb_pipe--;
// 	}
// 	if (prev_fd != -1)
// 		close(prev_fd);
// 	wait_for_all(shell, pid);
// }

