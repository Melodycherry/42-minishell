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

static int	create_and_check_fd(char *file);
static void	close_and_exit(t_shell *shell, int fd);
static void	expand_and_write(t_shell *shell, char *line, int fd, t_bool need_exp);

char	*create_name(t_shell *shell)
{
	char	*file;
	char	*index;

	index = ft_itoa(shell->executor.index_file_heredoc); //malloc ici
	if (!index)
		return (NULL); // faire une gestion d erreur ici
	file = ft_strjoin("/tmp/ms_hd_", index);
	if (!file)
		return (NULL); // faire une gestion d erreur ici
	free_ptr((void **)&index);
	return (file);
}

void	process_hd_file(t_shell *shell, char *file, char *eof, t_bool need_exp)
{
	pid_t	pid;
	int		fd;
	char	*line;

	pid = fork_process_or_exit();
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		fd = create_and_check_fd(file);
		while (1)
		{
			line = readline("> ");
			if (!line)
				return ;// faire gestion d erreur de sortie ici
			if (ft_strcmp(line, eof) == 0)
			{
				free_ptr((void **) &line);
				break ;
			}
			expand_and_write(shell, line, fd, need_exp);
			free_ptr((void **)&line);
		}
		close_and_exit(shell, fd);
	}
	wait_for_all(shell, pid);
}

static void	expand_and_write(t_shell *shell, char *line, int fd, t_bool need_exp)
{
	if (need_exp == TRUE)
		line = expand_all_vars_in_heredoc(shell, line);
	ft_putstr_fd(line, fd);
	ft_putstr_fd("\n", fd);
}

static int	create_and_check_fd(char *file)
{
	int	fd;

	fd = open(file, O_WRONLY | O_CREAT | O_EXCL | O_TRUNC, 0600);
	check_error_fd(fd);
	return (fd);
}

static void	close_and_exit(t_shell *shell, int fd)
{
	(void)shell;
	close(fd);
	exit(0); // faire mieux que ca
}
