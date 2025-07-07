/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlichten <hlichten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 20:29:57 by hlichten          #+#    #+#             */
/*   Updated: 2025/07/07 20:30:01 by hlichten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	nb_heredoc(t_shell *shell, t_token *token)
{
	shell->executor.nb_heredoc = 0;
	while (token->next)
	{
		if (token->type == T_HEREDOC)
			shell->executor.nb_heredoc++;
		token = token->next;
	}
}

void	heredoc_exit_eof(t_shell *shell, int fd)
{
	ft_putendl_fd("syntax error: unexpected end of file", STDERR_FILENO);
	close_fd(&fd);
	free_all(shell);
	exit(1);
}

void	close_and_exit(t_shell *shell, int fd)
{
	(void)shell;
	close_fd(&fd);
	free_all(shell);
	exit(0);
}

void	unlink_file(t_shell *shell)
{
	int		i;
	char	*stri;
	char	*file;

	i = 1;
	while (i <= shell->executor.nb_heredoc)
	{
		stri = ft_itoa(i);
		if (!stri)
			unfructuous_malloc(shell);
		file = ft_strjoin("/tmp/ms_hd_", stri);
		if (!file)
		{
			free_ptr((void **)&stri);
			unfructuous_malloc(shell);
		}
		unlink(file);
		free_ptr((void **)&stri);
		free_ptr((void **)&file);
		i++;
	}
}
