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

void set_redir_type(t_shell *shell, char *redir)
{
	if (ft_strcmp(redir, ">") == 0 )
		shell->executor.redir_type = T_REDIR_OUT;
	if (ft_strcmp(redir, "<<") == 0)
		shell->executor.redir_type = T_REDIR_APPEND;
	if (ft_strcmp(redir, "<") == 0)
		shell->executor.redir_type = T_REDIR_IN;
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

t_bool	is_redir(char *av)
{
	if (ft_strcmp(av, ">") == 0 || ft_strcmp(av, "<<") == 0
			|| ft_strcmp(av, "<") == 0)
		return (TRUE);
	else
		return (FALSE);
}
