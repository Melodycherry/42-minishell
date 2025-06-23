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

void	exec_pipe(t_shell *shell)
{
	int		fd_pipe[2];
	int		prev_fd;
	int		nb_pipe;
	pid_t	pid;
	char	**pipe_av;

	prev_fd = -1;
	nb_pipe = shell->executor.nb_pipe;
	init_pipe(shell);
	while (nb_pipe >= 0)
	{
		pipe_av = split_args(shell, shell->executor.av);
		create_pipe_or_exit(fd_pipe);
		pid = fork_process_or_exit();
		if (pid == 0)
		{
			check_fd(prev_fd);
			exec_pipe_child(shell, fd_pipe, pipe_av, nb_pipe);
		}
		prev_fd = update_parent_fds(fd_pipe, prev_fd, nb_pipe);
		update_executor_state(shell, pipe_av);
		nb_pipe--;
	}
	wait_for_all(pid);
}

void	create_pipe_or_exit(int *fd_pipe)
{
	if (pipe(fd_pipe) == -1)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
}

pid_t	fork_process_or_exit(void)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	return (pid);
}

void	check_fd(int prev_fd)
{
	if (prev_fd != -1)
	{
		dup2(prev_fd, STDIN_FILENO);
		close(prev_fd);
	}
}

void	exec_pipe_child(t_shell *shell, int *fd_pipe, char **pipe_av,
	int nb_pipe)
{
	if (nb_pipe > 0)
	{
		close(fd_pipe[0]);
		dup2(fd_pipe[1], STDOUT_FILENO);
		close(fd_pipe[1]);
	}
	exec_path(shell, pipe_av[0], pipe_av, shell->cmd.envp_copy);
	exit(EXIT_FAILURE);
}
