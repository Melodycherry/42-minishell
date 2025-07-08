/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlichten <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 20:31:03 by hlichten          #+#    #+#             */
/*   Updated: 2025/07/08 01:40:15 by hlichten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	find_range(t_shell *shell)
{
	int	i;

	i = shell->executor.start;
	if (i != 0 || shell->executor.start != 0)
		i++;
	shell->executor.start = i;
	while (shell->executor.av[i])
	{
		if (ft_strcmp(shell->executor.av[i], "|") == 0)
			break ;
		i++;
	}
	shell->executor.end = i - 1;
}

char	**split_args(t_shell *shell, char **av)
{
	char	**dest;
	int		i;
	int		start;
	int		end;

	find_range(shell);
	i = 0;
	start = shell->executor.start;
	end = shell->executor.end;
	dest = malloc(sizeof(char *) * (end - start + 2));
	if (!dest)
		unfructuous_malloc(shell);
	while (start <= end && av[start])
	{
		dest[i] = ft_strdup(av[start]);
		if (!dest[i])
			free_mid_tab(shell, &dest, i);
		i++;
		start++;
	}
	dest[i] = NULL;
	return (dest);
}

void	nb_pipe(t_shell *shell, t_token *token)
{
	shell->executor.nb_pipe = 0;
	while (token->next)
	{
		if (token->type == T_PIPE)
			shell->executor.nb_pipe++;
		token = token->next;
	}
}

void	dup_fd_stdin(t_shell *shell, t_bool is_saved_fd)
{
	if (is_saved_fd)
	{
		handle_dup2(shell, shell->fd.saved_stdin, STDIN_FILENO);
		close_fd(&shell->fd.saved_stdin);
	}
	else
	{
		if (shell->fd.prev_fd != -1)
		{
			handle_dup2(shell, shell->fd.prev_fd, STDIN_FILENO);
			close_fd(&shell->fd.prev_fd);
		}
	}
}

void	dup_fd_stdout(t_shell *shell, t_bool is_saved_fd)
{
	if (is_saved_fd)
	{
		handle_dup2(shell, shell->fd.saved_stdout, STDOUT_FILENO);
		close_fd(&shell->fd.saved_stdout);
	}
	else
	{
		handle_dup2(shell, shell->fd.fd_pipe[1], STDOUT_FILENO);
		close_fd(&shell->fd.fd_pipe[1]);
	}
}
