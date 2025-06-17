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

// void	update_executor_state(t_shell *shell, char **pipe_av)
// {
// 	free_tab(shell, pipe_av);
// 	shell->executor.end++;
// 	shell->executor.start = shell->executor.end;
// }

void	wait_for_all(void)
{
	while (wait(NULL) > 0)
		;
}
