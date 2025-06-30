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

void	update_executor_state(t_shell *shell, char **pipe_av)
{
	free_tab(&pipe_av);
	shell->executor.end++;
	shell->executor.start = shell->executor.end;
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
	{
		free_all(shell); // FIXME: test
		exit(EXIT_FAILURE); // TODO: faire une gestion d erreur ici , free et compagnie 
	}
		value = ft_strjoin("?=", str_exit_status);
	if (!value)
	{
		free_all(shell); // FIXME: test
		exit(EXIT_FAILURE); // TODO: faire une gestion d erreur ici , free et compagnie
	}
	free_ptr((void **) &str_exit_status);
	set_env(value, TO_ENV, shell);
	free_ptr((void **) &value);
}

