/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_file_creation.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlichten <hlichten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 20:30:05 by hlichten          #+#    #+#             */
/*   Updated: 2025/07/07 20:30:07 by hlichten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	create_and_check_fd(t_shell *shell, char *file);
static void	expand_and_write(t_shell *shell, char *line, int fd,
				t_bool need_exp);
static void	read_and_write_heredoc(t_shell *shell, char *eof, t_bool need_exp);

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

void	process_hd_file(t_shell *shell, char *file, char *eof, t_bool need_exp)
{
	pid_t	pid;

	heredoc_parent_signal();
	pid = fork_process_or_exit(shell);
	if (pid == 0)
	{
		heredoc_child_signal();
		create_and_check_fd(shell, file);
		free_ptr((void **) &file);
		read_and_write_heredoc(shell, eof, need_exp);
		close_and_exit(shell, shell->fd.fd_heredoc);
	}
	wait_for_all(shell, pid);
	parent_signal();
}

static void	create_and_check_fd(t_shell *shell, char *file)
{
	shell->fd.fd_heredoc = open
		(file, O_WRONLY | O_CREAT | O_EXCL | O_TRUNC, 0600);
	check_error_fd(shell, shell->fd.fd_heredoc);
}

static void	read_and_write_heredoc(t_shell *shell, char *eof, t_bool need_exp)
{
	char	*line;

	line = NULL;
	while (1)
	{
		line = readline("> ");
		if (!line)
			heredoc_exit_eof(shell, shell->fd.fd_heredoc);
		if (ft_strcmp(line, eof) == 0)
		{
			free_ptr((void **)&line);
			break ;
		}
		expand_and_write(shell, line, shell->fd.fd_heredoc, need_exp);
		free_ptr((void **)&line);
	}
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
