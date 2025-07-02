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

static int	create_and_check_fd(t_shell *shell, char *file);
static void	expand_and_write(t_shell *shell, char *line, int fd,
				t_bool need_exp);
static void	read_and_write_heredoc(t_shell *shell, int fd, char *eof,
				t_bool need_exp);

char	*create_name(t_shell *shell)
{
	char	*file;
	char	*index;

	index = ft_itoa(shell->executor.index_file_heredoc);
	if (!index)
		unfructuous_malloc(shell);
	file = ft_strjoin("/tmp/ms_hd_", index);
	if (!file)
	{
		free_ptr((void **)&index);
		unfructuous_malloc(shell);
	}
	free_ptr((void **)&index);
	return (file);
}

static void	read_and_write_heredoc(t_shell *shell, int fd, char *eof,
			t_bool need_exp)
{
	char	*line;

	line = NULL;
	while (1)
	{
		line = readline("> ");
		if (!line)
			heredoc_exit_eof(shell, fd);
		if (ft_strcmp(line, eof) == 0)
		{
			free_ptr((void **)&line);
			break ;
		}
		expand_and_write(shell, line, fd, need_exp);
		free_ptr((void **)&line);
	}
}

void	process_hd_file(t_shell *shell, char *file, char *eof, t_bool need_exp)
{
	pid_t	pid;
	int		fd;

	pid = fork_process_or_exit(shell);
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		fd = create_and_check_fd(shell, file);
		free_ptr((void **) &file);
		read_and_write_heredoc(shell, fd, eof, need_exp);
		close_and_exit(shell, fd);
	}
	wait_for_all(shell, pid);
}

static void	expand_and_write(t_shell *shell, char *line, int fd,
			t_bool need_exp)
{
	char	*new_line;

	if (need_exp == TRUE)
		new_line = expand_all_vars_in_heredoc(shell, line);
	else
	{
		new_line = ft_strdup(line);
		if (!new_line)
			unfructuous_malloc(shell);
	}
	ft_putstr_fd(new_line, fd);
	ft_putstr_fd("\n", fd);
	free_ptr((void **)&new_line);
}

static int	create_and_check_fd(t_shell *shell, char *file)
{
	int	fd;

	fd = open(file, O_WRONLY | O_CREAT | O_EXCL | O_TRUNC, 0600);
	check_error_fd(shell, fd);
	return (fd);
}
