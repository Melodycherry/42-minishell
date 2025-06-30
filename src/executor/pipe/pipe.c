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

void exec_pipe(t_shell *shell) // TODO: a refacto 
{
	pid_t	pid;
	int		prev_fd = -1;
	int		fd_pipe[2];
	int		nb_pipe;
	char	**pipe_av;

	init_pipe(shell);
	nb_pipe = shell->executor.nb_pipe;
	while (nb_pipe >= 0)
	{
		pipe_av = split_args(shell, shell->executor.av);
		if (nb_pipe > 0)
			create_pipe_or_exit(fd_pipe);
		else
		{
			fd_pipe[0] = -1;
			fd_pipe[1] = -1;
		}
		pid = fork_process_or_exit();
		if (pid == 0)
		{
			check_fd(prev_fd);
			exec_pipe_child(shell, fd_pipe, pipe_av, nb_pipe);
		}
		if (prev_fd != -1)
			close(prev_fd);

		if (nb_pipe > 0)
		{
			close(fd_pipe[1]);
			prev_fd = fd_pipe[0];
		}
		else
			prev_fd = -1;

		update_executor_state(shell, pipe_av);
		nb_pipe--;
	}
	if (prev_fd != -1)
		close(prev_fd);
	wait_for_all(shell, pid);
}

// chekc pour la refacto
// void	update_parent_fds(int prev_fd, int *fd_pipe)
// {
// 	if (prev_fd != -1)
// 			close(prev_fd);
// 	if (nb_pipe > 0)
// 	{
// 		close(fd_pipe[1]);
// 		prev_fd = fd_pipe[0];
// 	}
// 	else
// 		prev_fd = -1;
// }

void	create_pipe_or_exit(int *fd_pipe)
{
	if (pipe(fd_pipe) == -1)
	{
		perror("pipe");
		//free_all(shell); // FIXME: test
		exit(EXIT_FAILURE); //TODO: gestion erreur a faire , free avant d exit 
	}
}

pid_t	fork_process_or_exit(void)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		//free_all(shell); // FIXME: test
		exit(EXIT_FAILURE); //TODO: gestion erreur a faire , free avant d exit 
	}
	return (pid);
}

void	check_fd(int prev_fd)
{
	if (prev_fd != -1)
	{
		dup2(prev_fd, STDIN_FILENO); // TODO: fonction dup2 ?
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
	free_tab(&pipe_av); //
	free_all(shell); // FIXME: test
	exit(EXIT_FAILURE);
}
