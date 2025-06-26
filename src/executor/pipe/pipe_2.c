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

void	wait_for_all(t_shell *shell, pid_t pid)
{
	int	stat_loc;
	int exit_status;
	char *str_exit_status;
	char *value;

	if (pid > 0)
		waitpid(pid, &stat_loc, 0);
	if (WIFEXITED(stat_loc) == TRUE)
		exit_status = WEXITSTATUS(stat_loc); // de 0 a 127 les commandes 
	else if (WIFSIGNALED(stat_loc) == TRUE)
		exit_status = 128 + WTERMSIG(stat_loc); // pour les signaux car termsig retour le signal (de 1 a 31) donc pour pas confondre
	else
		exit_status = EXIT_FAILURE;
	str_exit_status = ft_itoa(exit_status);
	if(!str_exit_status)
		exit(EXIT_FAILURE); // faire une gestion d erreur ici , free et compagnie 
	value = ft_strjoin("?=", str_exit_status);
	if (!value)
		exit(EXIT_FAILURE); // faire une gestion d erreur ici , free et compagnie 
	set_env(value, TO_ENV, shell);
	}
	

	// faire une fonction avec ca 
	// str_exit_status = ft_itoa(exit_status);
	// if(!str_exit_status)
	// 	exit(EXIT_FAILURE); // faire une gestion d erreur ici , free et compagnie 
	// value = ft_strjoin("?=", str_exit_status);
	// if (!value)
	// 	exit(EXIT_FAILURE); // faire une gestion d erreur ici , free et compagnie 
	// set_env(value, TO_ENV, shell);
			
	
	
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