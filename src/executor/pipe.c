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

int	donne_moi_le_count(char **av)
{
	int count;
	int i = 0;

	count = 0;
	while (av[i] && ft_strcmp(av[i], "|") != 0)
	{
		count++;
		(i)++;
	}
	count++;
	return (count);
}
void exec_pipe(t_shell *shell)
{	
	int		fd_pipe[2];
	pid_t	pid_left;
	pid_t	pid_right;
	int 	count = 0;

	if (pipe(fd_pipe) == -1)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
	pid_left = fork();
	shell->executor.is_forked = TRUE;
	if (pid_left == -1) 
	{
		perror("fork left");
		exit(EXIT_FAILURE);
	}
	if (pid_left == 0) 
	{
		dup2(fd_pipe[1], STDOUT_FILENO); 
		close(fd_pipe[1]); // Ferme l’écriture après usage
		close(fd_pipe[0]); // Ferme la lecture
		complexe_exec_lol(shell, shell->executor.av[0], &shell->executor.av[count], shell->cmd.envp_copy); // peut etre prendre le export
		exit(EXIT_SUCCESS);
	}
	pid_right = fork();
	shell->executor.is_forked = TRUE;
	if (pid_right == -1)
	{
		perror("fork right");
		exit(EXIT_FAILURE);
	}
	if (pid_right == 0)
	{
		count = donne_moi_le_count(shell->executor.av);
		fprintf(stderr, "fucking count %d\n", count);
		dup2(fd_pipe[0], STDIN_FILENO); 
		close(fd_pipe[0]); // Ferme la lecture après usage
		close(fd_pipe[1]); // Ferme l’écriture
		complexe_exec_lol(shell, shell->executor.av[count], &shell->executor.av[count], shell->cmd.envp_copy); // peut etre prendre le export
		exit(EXIT_SUCCESS);
	}
	close(fd_pipe[0]);
	close(fd_pipe[1]);
	waitpid(pid_left, NULL, 0);
	waitpid(pid_right, NULL, 0);
}

void	pipe_exist(t_shell *shell, t_token *token)
{
	shell->executor.pipe_exist = FALSE;
	while (token->next)
	{
		if(token->type == T_PIPE)
			shell->executor.pipe_exist = TRUE;
		token = token->next;
	}
}
