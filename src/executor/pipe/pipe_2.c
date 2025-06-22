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

void	init_pipe(t_shell *shell)
{
	shell->executor.start = 0;
	shell->executor.end = 0;
}

int	update_parent_fds(int *fd_pipe, int prev_fd, int nb_pipe)
{
	if (prev_fd != -1)
		close(prev_fd);
	if (nb_pipe > 0)
	{
		close(fd_pipe[1]);
		return (fd_pipe[0]);
	}
	return (-1);
}

void	update_executor_state(t_shell *shell, char **pipe_av)
{
	free_tab(shell, pipe_av);
	shell->executor.end++;
	shell->executor.start = shell->executor.end;
}

void	wait_for_all(void)
{
	while (wait(NULL) > 0)
		;

		// faiur eun systeme qui va wait les pid



		/*
	WIFEXITED(status)
             True if the process terminated normally by a call to _exit(2) or exit(3).

     WIFSIGNALED(status)
             True if the process terminated due to receipt of a signal.

     Depending on the values of those macros, the following macros produce the remaining status information about the child process:

     WEXITSTATUS(status)
             If WIFEXITED(status) is true, evaluates to the low-order 8 bits of the argument passed to _exit(2) or exit(3) by the child.

     WTERMSIG(status)
             If WIFSIGNALED(status) is true, evaluates to the number of the signal that caused the termination of the process.
		*/
}
