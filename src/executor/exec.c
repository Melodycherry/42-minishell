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


// fonction de gestion de l execution
// ****** en cours ***********
void	execution(t_shell *shell)
{
	char *path;

	create_av(shell, shell->tlist.head);
	//if (shell->executor.av[0] == builtin); // WIP BY MELO
	
	// else // WIP BY GIGI

	if (is_absolative(shell->executor.av[0]))
	{
		exec_fork(shell, shell->executor.av[0], shell->executor.av, shell->cmd.envp_exp);
		printf("that s absolative\n");
	}
	else 
	{
		create_path(shell, shell->cmd.envp_exp);
		path = right_path(shell->executor.paths, shell->executor.av[0]);
		if (path)
		{
			exec_fork(shell, path, shell->executor.av, shell->cmd.envp_exp);
			free(path);
		}
	}
}

// fonction qui va checker si le path existe via le access sur le while du pathS
// ***** en cours *****
char	*right_path(char **paths, char *cmd)
{
	int i;
	char *path;
	
	i = 0;
	while (paths[i])
	{
		path = strjoin_malloc(paths[i], cmd);
		if (!access(path, F_OK))
		{
			if (!access(path, X_OK))
				return (path);
			//else
			// 	gestion d erreur
		}	
		free(path);
		path = NULL;
		i++;
	}
	// gestion d erreur
	return (NULL);
}

// focntion qui va checker l existance d un / pour determiner si c est absolative (absolu ou relative)
// faire les gestion des  edges cases de type juste des.. ou juste des / ou what // faire jour de la correction loool
// ******* a tester ***********
t_bool	is_absolative(char *str)
{
	if (ft_strchr(str, '/'))
		return (TRUE);
	return (FALSE);
}

//join qui malloc et renvoie le path + cmd
// *** seems to work., ya un malloc donc pas oublier de free :) ***
char	*strjoin_malloc(char *s1, char *s2)
{
	char	*dest;
	int		len;

	len = ((ft_strlen(s1)) + (ft_strlen(s2)));
	dest = (char *) malloc(sizeof(char) * (len + 2));
	if (dest == NULL)
		return (NULL);

	dest = ft_strjoin(&s1[4], "/");
	dest = ft_strjoin(dest, s2);
	return (dest);
}

// va faire l exec dans le child et pas le parent. Cest le cas pour toutes les execs hors builtin.
// ***** en cours, dont judge **** 
void	exec_fork(t_shell *shell, char *pathname, char **av, char **envp)
{
	pid_t	pid;
	int		stat_pid;

	if (shell->executor.is_forked == FALSE)
	{
		pid = fork();
		if (pid == -1)
		{
			return (perror("fork"));
		}
		if (pid > 0) // permet d attendre la fin de l execution du child !
			waitpid(pid, &stat_pid, 0);

		if (pid == 0) //on va aller faire le process dans la partie qui est enfant = le pid est de 0;
		{
			execve(pathname, av, envp);
			perror("Error :"); // gestion d erreur a faire
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		// situation si on a un pipe en cours mais pour l instant fuck off
	}

}

// On success, execve() does not return, on error -1 is returned, and errno is set appropriately.