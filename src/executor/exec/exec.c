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

static void	set_exit_status_env(int exit_status, t_shell *shell);
static void	exec_with_redir_check(t_shell *shell, char *pathname, char **av);

void	execution(t_shell *shell)
{
	int		exit_status;
	int		saved_stdin;
	int		saved_stdout;

	nb_pipe(shell, shell->tlist.head);
	create_av(shell, shell->tlist.head);
	if (!shell || !shell->executor.av || !shell->executor.av[0])
		return ;
	if (is_builtin(shell->executor.av[0]) && shell->executor.nb_pipe == 0)
	{
		saved_stdin = dup(STDIN_FILENO);
		saved_stdout = dup(STDOUT_FILENO);
		set_redir_count(shell, shell->executor.av);
		exit_status = exec_builtin(shell);
		set_exit_status_env(exit_status, shell);
		handle_dup2(shell, saved_stdin, STDIN_FILENO);
		handle_dup2(shell, saved_stdout, STDOUT_FILENO);
		close(saved_stdin);
		close(saved_stdout);
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
		close(fd);
		free_all(shell);
		exit(EXIT_FAILURE);
	}
}

static void	set_exit_status_env(int exit_status, t_shell *shell)
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

static void	exec_with_redir_check(t_shell *shell, char *pathname, char **av)
{
	set_redir_count(shell, av);
	if (shell->executor.nb_redir > 0)
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

void	exec_fork(t_shell *shell, char *pathname, char **av)
{
	pid_t	pid;

	if (shell->executor.is_forked == FALSE)
	{
		pid = fork();
		if (pid == -1)
			return (perror("fork"));
		if (pid > 0)
			wait_for_all(shell, pid);
		if (pid == 0)
			exec_with_redir_check(shell, pathname, av);
	}
	else
	{
		shell->executor.is_forked = FALSE;
		exec_with_redir_check(shell, pathname, av);
	}
}
