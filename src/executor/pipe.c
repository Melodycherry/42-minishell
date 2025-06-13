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

void exec_pipe(t_shell *shell)
{	
	int		fd_pipe[2];
	int		prev_fd = -1;
	int		nb_pipe;
	pid_t	pid;
	char	**pipe_av;

	nb_pipe = shell->executor.nb_pipe;
	shell->executor.start = 0;
	shell->executor.end = 0;
	while (nb_pipe >= 0)
	{
		pipe_av = split_args(shell, shell->executor.av);
		if (pipe(fd_pipe) == -1)
		{
			perror("pipe");
			exit(EXIT_FAILURE);
		}
		pid = fork();
		if (pid == -1)
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}
		if (pid == 0)
		{
			if (prev_fd != -1)
			{
				dup2(prev_fd, STDIN_FILENO);
				close(prev_fd);
			}
			if (nb_pipe > 0)
			{
				close(fd_pipe[0]);
				dup2(fd_pipe[1], STDOUT_FILENO);
				close(fd_pipe[1]);
			}
			complexe_exec_lol(shell, pipe_av[0], pipe_av, shell->cmd.envp_copy);
			exit(EXIT_FAILURE);
		}
		if (prev_fd != -1)
			close(prev_fd);
		if (nb_pipe)
		{
			close(fd_pipe[1]);
			prev_fd = fd_pipe[0];
		}
		else
			prev_fd = -1;
		free_tab(shell, pipe_av);
		shell->executor.end++;
		shell->executor.start = shell->executor.end;
		nb_pipe--;
	}
	while (wait(NULL) > 0)
		;
}
















// la version qui fait que 2 pipes

// void exec_pipe(t_shell *shell)
// {	
// 	int		fd_pipe[2];
// 	pid_t	pid_left;
// 	pid_t	pid_right;
// 	char	**av_left;
// 	char	**av_right;

// 	av_left = split_args(shell, shell->executor.av);
// 	// print_tab(av_left);
// 	// printf("\n");
// 	if (shell->executor.av[shell->executor.end + 1])
// 		shell->executor.end ++;
// 	av_right = split_args(shell, shell->executor.av);
// 	//print_tab(av_right);
	
// 	if (pipe(fd_pipe) == -1)
// 	{
// 		perror("pipe");
// 		exit(EXIT_FAILURE);
// 	}

// 	pid_left = fork();
// 	shell->executor.is_forked = TRUE;
	
// 	if (pid_left == -1) 
// 	{
// 		perror("fork left");
// 		exit(EXIT_FAILURE);
// 	}

// 	if (pid_left == 0) 
// 	{
// 		close(fd_pipe[0]); // Ferme la lecture
// 		dup2(fd_pipe[1], STDOUT_FILENO); 
// 		close(fd_pipe[1]); // Ferme l’écriture après usage
// 		complexe_exec_lol(shell, av_left[0], av_left, shell->cmd.envp_copy); // peut etre prendre le export
// 		perror("execve pid_left");
// 		exit(EXIT_SUCCESS);
// 	}

// 	pid_right = fork();
// 	shell->executor.is_forked = TRUE;
// 	if (pid_right == -1)
// 	{
// 		perror("fork right");
// 		exit(EXIT_FAILURE);
// 	}

// 	if (pid_right == 0)
// 	{
// 		close(fd_pipe[1]); // Ferme l’écriture
// 		dup2(fd_pipe[0], STDIN_FILENO); 
// 		close(fd_pipe[0]); // Ferme la lecture après usage
// 		complexe_exec_lol(shell, av_right[0], av_right, shell->cmd.envp_copy); // peut etre prendre le export
// 		exit(EXIT_SUCCESS);
// 	}

// 	close(fd_pipe[0]);
// 	close(fd_pipe[1]);
// 	waitpid(pid_left, NULL, 0);
// 	waitpid(pid_right, NULL, 0);
// 	free_tab(shell, av_left);
// 	free_tab(shell, av_right);
// }