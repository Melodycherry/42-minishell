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

void	create_pipe_or_exit(t_shell *shell)
{
	if (pipe(shell->fd.fd_pipe) == -1)
	{
		perror("pipe");
		free_all(shell);
		exit(EXIT_FAILURE);
	}
}

pid_t	fork_process_or_exit(t_shell *shell)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		free_all(shell);
		exit(EXIT_FAILURE);
	}
	return (pid);
}
