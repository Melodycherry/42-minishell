/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlichten <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 20:31:31 by hlichten          #+#    #+#             */
/*   Updated: 2025/07/08 01:42:27 by hlichten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	exec_with_redir_check(t_shell *shell, char *pathname, char **av);

void	execution(t_shell *shell)
{
	int		exit_status;

	nb_pipe(shell, shell->tlist.head);
	convert_list_to_av(shell, shell->tlist.head);
	if (!shell || !shell->executor.av || !shell->executor.av[0])
		return ;
	if ((is_builtin(shell->executor.av[0]) && shell->executor.nb_pipe == 0))
	{
		shell->fd.saved_stdin = dup(STDIN_FILENO);
		shell->fd.saved_stdout = dup(STDOUT_FILENO);
		process_all_redirections(shell, shell->executor.av);
		exit_status = exec_builtin(shell, FALSE);
		set_exit_status_env(shell, exit_status);
		dup_fd_stdin(shell, TRUE);
		dup_fd_stdout(shell, TRUE);
		free_tab(&shell->executor.redir_av);
	}
	else if (shell->executor.nb_pipe > 0)
		exec_pipe(shell);
	else
		exec_path(shell, shell->executor.av[0], shell->executor.av);
}

void	handle_dup2(t_shell *shell, int fd, int std)
{
	if (dup2(fd, std) == -1)
	{
		perror("dup2");
		close_fd(&fd);
		free_all(shell);
		exit(EXIT_FAILURE);
	}
}

void	set_exit_status_env(t_shell *shell, int exit_status)
{
	char	*str_exit_status;
	char	*value;

	str_exit_status = ft_itoa(exit_status);
	if (!str_exit_status)
	{
		ft_putendl_fd("Malloc error (itoa)\n", STDERR_FILENO);
		free_all(shell);
		exit(EXIT_FAILURE);
	}
	value = ft_strjoin("?=", str_exit_status);
	if (!value)
	{
		ft_putendl_fd("Malloc error (strjoin)\n", STDERR_FILENO);
		free_all(shell);
		free_ptr((void **)&str_exit_status);
		exit(EXIT_FAILURE);
	}
	free_ptr((void **)&str_exit_status);
	set_env(value, TO_ENV, shell);
	free_ptr((void **)&value);
}

void	exec_fork(t_shell *shell, char *pathname, char **av)
{
	pid_t	pid;

	if (shell->executor.is_forked == FALSE)
	{
		pid = fork_process_or_exit(shell);
		shell->executor.is_forked = TRUE;
		sig_core_dump_parent_signal();
		if (pid == 0)
			exec_with_redir_check(shell, pathname, av);
		wait_for_all(shell, pid);
		free_ptr((void **)&pathname);
		parent_signal();
	}
	else
		exec_with_redir_check(shell, pathname, av);
}

static void	exec_with_redir_check(t_shell *shell, char *pathname, char **av)
{
	if (shell->executor.is_forked == FALSE)
		child_signal();
	process_all_redirections(shell, av);
	shell->executor.is_forked = FALSE;
	if (shell->executor.nb_redir > 0 || shell->executor.is_redir_beg == TRUE)
	{
		shell->executor.nb_redir = 0;
		execve(pathname, shell->executor.redir_av, shell->cmd.envp_exp);
		perror("Error");
		exit(EXIT_FAILURE);
	}
	else
	{
		execve(pathname, av, shell->cmd.envp_exp);
		perror("Error");
		exit(EXIT_FAILURE);
	}
}
