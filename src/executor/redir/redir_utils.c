/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlichten <hlichten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 20:30:31 by hlichten          #+#    #+#             */
/*   Updated: 2025/07/07 20:30:35 by hlichten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_redir_in(t_shell *shell, char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	check_error_fd(shell, fd);
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		perror("dup2");
		close(fd);
		free_all(shell);
		exit(EXIT_FAILURE);
	}
	close(fd);
}

void	handle_redir_out(t_shell *shell, char *file)
{
	int	fd;

	fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	check_error_fd(shell, fd);
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		perror("dup2");
		close(fd);
		free_all(shell);
		exit(EXIT_FAILURE);
	}
	close(fd);
}

void	handle_redir_append(t_shell *shell, char *file)
{
	int	fd;

	fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	check_error_fd(shell, fd);
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		perror("dup2");
		close(fd);
		free_all(shell);
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

void	check_error_fd(t_shell *shell, int fd)
{
	if (fd < 0)
	{
		perror("open");
		free_all(shell);
		exit(EXIT_FAILURE);
	}
}
