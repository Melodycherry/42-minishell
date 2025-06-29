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

// fonction de gestion de l execution
// ****** en cours, fonctionne dans ce etat ***********

void	execution(t_shell *shell)
{
	int		exit_status;
	int		saved_stdin;
	int		saved_stdout;

	nb_pipe(shell, shell->tlist.head);
	create_av(shell, shell->tlist.head);
	if (!shell || !shell->executor.av || !shell->executor.av[0])
		return ;
	if (is_builtin(shell->executor.av[0]) == TRUE
		&& shell->executor.nb_pipe == 0)
	{
		saved_stdin = dup(STDIN_FILENO);
		saved_stdout = dup(STDOUT_FILENO);
		set_redir_count(shell, shell->executor.av);
		exit_status = exec_builtin(shell);
		set_exit_status_env(exit_status, shell);
		dup2(saved_stdin, STDIN_FILENO);
		dup2(saved_stdout, STDOUT_FILENO);
		close(saved_stdin);
		close(saved_stdout);
		free_tab(&shell->executor.redir_av);
	}
	else if (shell->executor.nb_pipe > 0)
	{
		exec_pipe(shell);
		free_tab(&shell->executor.redir_av);
	}
	else
	{
		exec_path(shell, shell->executor.av[0], shell->executor.av, shell->cmd.envp_exp);
		free_tab(&shell->executor.redir_av);
	}
}

void	set_exit_status_env(int exit_status, t_shell *shell)
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

// exec dans le child et pas le parent. toutes les execs hors builtin.
// ***** en cours, dont judge **** 

void	exec_with_redir_check(t_shell *shell, char *pathname, char **av, char **envp)
{
	set_redir_count(shell, av);
	if (shell->executor.nb_redir > 0)
	{
		free_child_redir(shell);
		shell->executor.nb_redir = 0;
		execve(pathname, shell->executor.redir_av, envp);
		free_tab(&shell->executor.redir_av);
		perror("Error"); // m eilleur message erreur
		exit(EXIT_FAILURE);
	}
	else
	{
		free_child_pipe(shell);
		execve(pathname, av, envp);
		perror("Error"); //meilleur mesdsage d erreur
		exit(EXIT_FAILURE);
	}
}

void	exec_fork(t_shell *shell, char *pathname, char **av, char **envp)
{
	pid_t	pid;

	if (shell->executor.is_forked == FALSE)
	{
		pid = fork();
		if (pid == -1)
			return (perror("fork")); // exit avec gestion d erreur et free
		if (pid > 0)
			wait_for_all(shell, pid);
		if (pid == 0)
			exec_with_redir_check(shell, pathname, av, envp);
	}
	else
	{
		shell->executor.is_forked = FALSE;
		exec_with_redir_check(shell, pathname, av, envp);
	}
}

// fonction qui va gerer l execution sans ces fdp de pipe :)))
// ***** en cours, fonctionne sous cet état, surement des leaks :)))))))))))***
void	exec_path(t_shell *shell, char *pathname, char **av, char **envp)
{
	char	*path;

	if (is_absolative(pathname))
		exec_fork(shell, pathname, av, envp);
	else
	{
		create_path(shell, shell->cmd.envp_exp);
		path = right_path(shell->executor.paths, pathname);
		if (path)
		{
			exec_fork(shell, path, av, envp);
			free_ptr((void **)&path);
		}
	}
}
