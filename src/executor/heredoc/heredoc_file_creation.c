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

char	*generate_file(t_shell *shell, t_token *token)
{
	char	*file;
	char	*eof;
	t_bool	need_exp;

	need_exp = TRUE;
	if (token->next)
	{
		eof = token->next->value;
		if (token->next->type == T_EOF_Q)
			need_exp = FALSE;
	}
	else
		return (NULL); //faire gestion d erreur ici
	file = create_name(shell);
	process_hd_file(shell, file, eof, need_exp);
	return (file);
}

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

//refacto ca quand melo aura fini avec Pieric 

void	process_hd_file(t_shell *shell, char *file, char *eof, t_bool need_exp)
{
	pid_t	pid;
	int		fd;
	char	*line;

	pid = fork_process_or_exit();
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		fd = open(file, O_WRONLY | O_CREAT | O_EXCL | O_TRUNC, 0600);
		check_error_fd(fd);
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
			if (need_exp == TRUE)
				line = expand_all_vars_in_heredoc(shell, line);
			ft_putstr_fd(line, fd);
			ft_putstr_fd("\n", fd);
			free_ptr((void **)&line);
		}
		close(fd);
		exit(0); // faire mieux que ca
	}
	wait_for_all(shell, pid);
}

