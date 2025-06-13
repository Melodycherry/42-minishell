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

// int	donne_moi_le_count(char **av)
// {
// 	int count;
// 	int i = 0;

// 	count = 0;
// 	while (av[i] && ft_strcmp(av[i], "|") != 0)
// 	{
// 		count++;
// 		(i)++;
// 	}
// 	count++;
// 	return (count);
// }

void find_range(t_shell *shell)
{
	int i;

	i = shell->executor.end;
	if (i != 0 || shell->executor.start != 0)
		i++;
	shell->executor.start = i;
	while (shell->executor.av[i])
	{
		if (ft_strcmp(shell->executor.av[i], "|") == 0)
			break;
		i++;
	}
	shell->executor.end = i - 1;
}

char	**split_args(t_shell *shell, char **av)
{
	char **dest; 
	int i;
	int start;
	int end;
	
	find_range(shell);
	i = 0;
	start = shell->executor.start;
	end = shell->executor.end;
	dest = malloc(sizeof(char *) * (end - start + 2));
	if (!dest)
		return (NULL);
	while (start <= end && av[start])
	{
		dest[i] = ft_strdup(av[start]);
		i++;
		start++;
	}
	dest[i] = NULL;
	return (dest);
}

void exec_pipe(t_shell *shell)
{	
	int		fd_pipe[2];
	pid_t	pid_left;
	pid_t	pid_right;
	char	**av_left;
	char	**av_right;

	av_left = split_args(shell, shell->executor.av);
	// print_tab(av_left);
	// printf("\n");
	if (shell->executor.av[shell->executor.end + 1])
		shell->executor.end ++;
	av_right = split_args(shell, shell->executor.av);
	//print_tab(av_right);
	
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
		close(fd_pipe[0]); // Ferme la lecture
		dup2(fd_pipe[1], STDOUT_FILENO); 
		close(fd_pipe[1]); // Ferme l’écriture après usage
		complexe_exec_lol(shell, av_left[0], av_left, shell->cmd.envp_copy); // peut etre prendre le export
		perror("execve pid_left");
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
		close(fd_pipe[1]); // Ferme l’écriture
		dup2(fd_pipe[0], STDIN_FILENO); 
		close(fd_pipe[0]); // Ferme la lecture après usage
		complexe_exec_lol(shell, av_right[0], av_right, shell->cmd.envp_copy); // peut etre prendre le export
		exit(EXIT_SUCCESS);
	}

	close(fd_pipe[0]);
	close(fd_pipe[1]);
	waitpid(pid_left, NULL, 0);
	waitpid(pid_right, NULL, 0);
	free_tab(shell, av_left);
	free_tab(shell, av_right);
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
