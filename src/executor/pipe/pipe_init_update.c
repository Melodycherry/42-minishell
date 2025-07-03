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

void	update_executor_state(t_shell *shell)
{
	free_tab(&shell->executor.pipe_av);
	shell->executor.end++;
	shell->executor.start = shell->executor.end;
}

void	update_parent_fds(int *prev_fd, int *fd_pipe, int nb_pipe)
{
	if (*prev_fd != -1)
		close(*prev_fd);
	if (nb_pipe > 0)
	{
		close(fd_pipe[1]);
		*prev_fd = fd_pipe[0];
	}
	else
		*prev_fd = -1;
}
