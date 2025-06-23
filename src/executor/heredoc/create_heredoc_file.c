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
		return NULL; // faire une gestion d erreur ici
	file = ft_strjoin("/tmp/ms_hd_", index);
	free_ptr((void **)&index);
	return (file);
}

void	process_hd_file(t_shell *shell, char *file, char *eof, t_bool need_exp)
{
	pid_t	pid;
	int		fd;	

	pid = fork_process_or_exit();
	if (pid == 0)
	{
		fd = open(file, O_WRONLY | O_CREAT | O_EXCL | O_TRUNC, 0600);
		check_error_fd(fd);
		while (1)
		{
			char *line = readline("> ");
			if (!line)
				return ; // faire gestion d erreur de sortie ici
			if (ft_strcmp(line, eof) == 0)
			{
				free_ptr((void **) &line);
				break ;
			}
			if (need_exp == TRUE)
				line = heredoc_variable_expansion(shell, line);
			ft_putstr_fd(line, fd);
			ft_putstr_fd("\n", fd);
			free_ptr((void **)&line);
		}
		close(fd);
		exit(0); // faire mieux que ca
	}
	wait_for_all(pid);
}

char *heredoc_variable_expansion(t_shell *shell, char *line)
{
	char 	*tmp;
	char	*rec_var;
	int 	i;
	int		j;

	j = 0;
	i = 0;
	tmp = NULL;
	while (line[i])
	{
		if (line[i] == '$')
		{
			if (i > j)
				tmp = join_free(tmp, &line[j], i - j); // text before $
			i++;
			j = i;
			while (line[i] && (ft_isalnum(line[i]) || line[i] == '_'))
				i++;
			if (i > j && var_exist(shell->cmd.envp_copy, &line[j], i - j))
			{
				rec_var = recup_var(shell->cmd.envp_copy, &line[j], i - j);
				tmp = join_free(tmp, rec_var, 0);
				free(rec_var);
			}
			j = i;
		}
		else
			i++;
	}
	if (i > j)
		tmp = join_free(tmp, &line[j], i - j);
	free(line);
	return tmp;
}

// char *expansion_hd(t_shell *shell, char *line, int *i, int *j)
// {
	
// }


// void	fill_heredoc_file(t_shell *shell, char *eof, int fd, t_bool need_exp)
// {
// 	while (1)
// 	{
// 		char *line = readline("> ");
// 		if (!line)
// 			return ; // faire gestion d erreur de sortie ici
// 		if (ft_strcmp(line, eof) == 0)
// 		{
// 			free_ptr((void **) &line);
// 			break ;
// 		}
// 		if (need_exp == TRUE)
// 			line = heredoc_variable_expansion(shell, line);
// 		ft_putstr_fd(line, fd);
// 		ft_putstr_fd("\n", fd);
// 		free_ptr((void **)&line);
// 	}
// }