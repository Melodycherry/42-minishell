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

void    execution(t_shell *shell)
{
	nb_pipe(shell, shell->tlist.head);
	create_av(shell, shell->tlist.head);
	if (!shell || !shell->executor.av || !shell->executor.av[0])
		return ;
	if (is_builtin(shell->executor.av[0]) == TRUE && shell->executor.nb_pipe == 0)
	{
		int	saved_stdin = dup(STDIN_FILENO);
		int	saved_stdout = dup(STDOUT_FILENO);
		set_redir_count(shell, shell->executor.av);
		shell->executor.redir_av = set_redir_av(shell->executor.av); // test
		exec_builtin(shell);
		dup2(saved_stdin, STDIN_FILENO);
		dup2(saved_stdout, STDOUT_FILENO);
		close(saved_stdin);
		close(saved_stdout);
	}
	else if (shell->executor.nb_pipe > 0)
		exec_pipe(shell);
	else
		exec_path(shell, shell->executor.av[0], shell->executor.av, shell->cmd.envp_exp);
}

// exec dans le child et pas le parent. toutes les execs hors builtin.
// ***** en cours, dont judge **** 

void exec_with_redir_check(t_shell *shell, char *pathname, char **av, char **envp)
{
	set_redir_count(shell, av);
	if (shell->executor.nb_redir > 0)
	{
		shell->executor.nb_redir = 0;
		execve(pathname, shell->executor.redir_av, envp);
		perror("Error");
		exit(EXIT_FAILURE);
	}
	else
	{
		execve(pathname, av, envp);
		perror("Error");
		exit(EXIT_FAILURE);
	}
}

void	exec_fork(t_shell *shell, char *pathname, char **av, char **envp)
{
	pid_t	pid;
	int		stat_pid;

	if (shell->executor.is_forked == FALSE)
	{
		pid = fork();
		if (pid == -1)
			return (perror("fork"));
		if (pid > 0)
			waitpid(pid, &stat_pid, 0);
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
			free(path);
		}
	}
}
