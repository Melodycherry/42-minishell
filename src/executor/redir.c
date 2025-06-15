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


// redirection en cours merci de ne pas juger lololol :) 


/* va verifier si presence de redir, les faire fonctionner et executer*/
/******** tout fonctionne sauf l execution ********/
void	redir_handle(t_shell *shell, char **av)
{
	redir_count_set(shell, av);
	t_token_type type;
	
	type = shell->executor.redir_type;
	
	printf("type = %d && after_redir = %s\n", type, shell->executor.redir_file);
	// if (type == T_REDIR_IN)
	// handle_redir_in(shell->executor.redir_file);
	// if (type == T_REDIR_OUT)
	// handle_redir_out(shell->executor.redir_file);
	// if (type == T_REDIR_APPEND)
	// handle_redir_append(shell->executor.redir_file);
}

/* fonction qui va compter le nb de redirection */
/*************** marche dans cet etat **************/
void	redir_count_set(t_shell *shell, char **av)
{
	int		i;

	i = 0;
	shell->executor.nb_redir = 0;
	while (av[i])
	{
		if (ft_strcmp(av[i], ">") == 0 || ft_strcmp(av[i], "<<") == 0
			|| ft_strcmp(av[i], "<") == 0)
			shell->executor.nb_redir++;
		i++;
	}
	if (shell->executor.nb_redir > 0)
			set_redir_file(shell, av);
}

/* va mettre en place les infos a chaque fois qu on voit un > < >> */
/************* seems ok ******************/
void	set_redir_file(t_shell *shell, char **av)
{
	int i;
	int	j;

	i = ft_tablen(av) - 1;
	j = shell->executor.nb_redir;
	while (i > 0 && j > 0)
	{
		if (ft_strcmp(av[i], ">") == 0 || ft_strcmp(av[i], "<<") == 0
			|| ft_strcmp(av[i], "<") == 0)
			{
				j--;
				if (j == 0)
					break;
			}
		i--;
	}
	shell->executor.nb_redir--;
	if (shell->executor.redir_file != NULL)
		free(shell->executor.redir_file);
	if (av[i + 1])
		shell->executor.redir_file = file_redir(av[i + 1]);
	else
		shell->executor.redir_file = NULL;
	set_redir_type(shell, av[i]);
}

void set_redir_type(t_shell *shell, char *redir)
{
	if (ft_strcmp(redir, ">") == 0 )
		shell->executor.redir_type = T_REDIR_OUT;
	if (ft_strcmp(redir, "<<") == 0)
		shell->executor.redir_type = T_REDIR_APPEND;
	if (ft_strcmp(redir, "<") == 0)
		shell->executor.redir_type = T_REDIR_IN;
}

char	*file_redir(char *file)
{
	char	*dest;
	char	*tmp;

	tmp = ft_strjoin("\"", file);
	if (!tmp)
		return (NULL);
	dest = ft_strjoin(tmp, "\"");
	free(tmp);
	return (dest);
}

void handle_redir_in(char *file)
{
	int fd;
	
	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		perror("open");
		exit(EXIT_FAILURE);
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
}

void handle_redir_out(char *file)
{
	int fd;
	
	fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		perror("open");
		exit(EXIT_FAILURE);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);	
}

void handle_redir_append(char *file)
{
	int fd;
	
	fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
	{
		perror("open");
		exit(EXIT_FAILURE);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);	
}


// cat < file.txt -> file.txt devient stdin
// echo hello > out.txt -> ecrit "hello" das out.txt (ecrase)
// echo again >> out.txt -> ajoute "again" a la fin de out.txt
