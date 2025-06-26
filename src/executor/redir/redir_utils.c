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

void handle_redir_in(char *file)
{
	int fd;
	
	fd = open(file, O_RDONLY);
	check_error_fd(fd);
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		perror("dup2");
		close(fd);
		exit(EXIT_FAILURE);
	}
	close(fd);
}

void handle_redir_out(char *file)
{
	int fd;

	fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	check_error_fd(fd);
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		perror("dup2");
		close(fd);
		exit(EXIT_FAILURE);
	}
	close(fd);
}

void handle_redir_append(char *file)
{
	int fd;
	
	fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	check_error_fd(fd);
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		perror("dup2");
		close(fd);
		exit(EXIT_FAILURE);
	}
	close(fd);	
}

t_bool	is_redir(char *av)
{
	if (ft_strcmp(av, ">") == 0 || ft_strcmp(av, ">>") == 0
			|| ft_strcmp(av, "<") == 0)
		return (TRUE);
	else
		return (FALSE);
}

void	check_error_fd(int fd)
{
	if (fd < 0)
	{
		perror("open");
		exit(EXIT_FAILURE); // meilleure gestion d erreur
	}
}
