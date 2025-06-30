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

void	print_token(t_token *token, int (*f)(const char *, ...))
{
	int i;

	i = 0;
	if (!f)
		return ;
	while (token)
	{
		(*f)("token[%d] %s\n", i, token->value);
		(*f)("token[%d] %d\n", i, token->type);
		(*f)("token[%d] %s\n", i, token->var_value);
		token = token->next;
		i++;
	}
}

void	print_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab && tab[i])
	{
		printf("%s\n", tab[i]);
		i++;
	}
}

// void	print_token2(t_token *token, int (*f)(const char *, ...))
// {
// 	int i;

// 	i = 0;
// 	if (!f)
// 		return ;
// 	while (token)
// 	{
// 		//(*f)("token[%d] %s\n", i, token->value);
// 		(*f)("token[%d] %d\n", i, token->type);
// 		token = token->next;
// 		i++;
// 	}
// }

// void	print_token3(t_token *token, int (*f)(const char *, ...))
// {
// 	int i;

// 	i = 0;
// 	if (!f)
// 		return ;
// 	while (token)
// 	{
// 		(*f)("token[%d] %s\n", i, token->var_value);
// 		//(*f)("token[%d] %s\n", i, token->type);
// 		token = token->next;
// 		i++;
// 	}
// }









/// DECHETS /// 


// si besoin mais on peut mettre ca dans le trash je pense
// void	simple_exec(t_shell *shell)
// {
// 	char *path;

// 	if (is_absolative(shell->executor.av[0]))
// 		exec_fork(shell, shell->executor.av[0], shell->executor.av, shell->cmd.envp_exp);
// 	else 
// 	{
// 		create_path(shell, shell->cmd.envp_exp);
// 		path = right_path(shell->executor.paths, shell->executor.av[0]);
// 		if (path)
// 		{
// 			exec_fork(shell, path, shell->executor.av, shell->cmd.envp_exp);
// 			free(path);
// 		}
// 	}
// }

// la version qui fait que 2 pipes

// void exec_pipe(t_shell *shell)
// {	
// 	int		fd_pipe[2];
// 	pid_t	pid_left;
// 	pid_t	pid_right;
// 	char	**av_left;
// 	char	**av_right;

// 	av_left = split_args(shell, shell->executor.av);
// 	// print_tab(av_left);
// 	// printf("\n");
// 	if (shell->executor.av[shell->executor.end + 1])
// 		shell->executor.end ++;
// 	av_right = split_args(shell, shell->executor.av);
// 	//print_tab(av_right);
	
// 	if (pipe(fd_pipe) == -1)
// 	{
// 		perror("pipe");
// 		exit(EXIT_FAILURE);
// 	}

// 	pid_left = fork();
// 	shell->executor.is_forked = TRUE;
	
// 	if (pid_left == -1) 
// 	{
// 		perror("fork left");
// 		exit(EXIT_FAILURE);
// 	}

// 	if (pid_left == 0) 
// 	{
// 		close(fd_pipe[0]); // Ferme la lecture
// 		dup2(fd_pipe[1], STDOUT_FILENO); 
// 		close(fd_pipe[1]); // Ferme l’écriture après usage
// 		complexe_exec_lol(shell, av_left[0], av_left, shell->cmd.envp_copy); // peut etre prendre le export
// 		perror("execve pid_left");
// 		exit(EXIT_SUCCESS);
// 	}

// 	pid_right = fork();
// 	shell->executor.is_forked = TRUE;
// 	if (pid_right == -1)
// 	{
// 		perror("fork right");
// 		exit(EXIT_FAILURE);
// 	}

// 	if (pid_right == 0)
// 	{
// 		close(fd_pipe[1]); // Ferme l’écriture
// 		dup2(fd_pipe[0], STDIN_FILENO); 
// 		close(fd_pipe[0]); // Ferme la lecture après usage
// 		complexe_exec_lol(shell, av_right[0], av_right, shell->cmd.envp_copy); // peut etre prendre le export
// 		exit(EXIT_SUCCESS);
// 	}

// 	close(fd_pipe[0]);
// 	close(fd_pipe[1]);
// 	waitpid(pid_left, NULL, 0);
// 	waitpid(pid_right, NULL, 0);
// 	free_tab(shell, av_left);
// 	free_tab(shell, av_right);
// }


// char	*file_redir(char *file)
// {
// 	char	*dest;
// 	char	*tmp;

// 	tmp = ft_strjoin("\"", file);
// 	if (!tmp)
// 		return (NULL);
// 	dest = ft_strjoin(tmp, "\"");
// 	free(tmp);
// 	return (dest);
// }


// int	donne_moi_le_count(char **av)
// {
// 	int count;
// 	int i = 0;

// 	count = 0;
// 	while (av[i] && ft_strcmp(av[i], "|") != 0)
// 	{
// 		count++;
// 		(i)++;
// 	}
// 	count++;
// 	return (count);
// }



// //pour l instant sert a rien mais risque de servir
// // **** a tester ****
// t_bool is_valid_var_name(t_token *token, t_shell *shell)
// {
// 	int		i;
// 	char	*line;
	
// 	(void)shell;
// 	i = 0;
// 	line = token->value;
// 	while (line[i] && line[i] != '=')
// 	{
// 		if (line[0] == '_' || ft_isalpha(line[0]))
// 			i++;
// 		else 
// 			return (FALSE);
// 		if (line[i] == '_' || ft_isalnum(line[i]))
// 			i++;
// 	}
// 	return (TRUE);
// }



// tokensisation en fonction si on trouve des ' ' ou des "" et ''

// int	count_quotes(t_shell *shell, char quote, char c)
// {
// 	int		i;
// 	char	*line;
// 	int 	nb_quote;

// 	i = 0;
// 	nb_quote = 0;
// 	line = shell->cmd.line;
// 	while (line[i])
// 	{
// 		if (line[i] == quote)
// 		{
// 			nb_quote++;
// 			i++;
// 			while (line[i] && line[i] != c)
// 				i++;
// 			if(line[i] == c)
// 				nb_quote++;
// 		}
// 		i++;
// 	}
// 	return (nb_quote);
// }

// int	count_single_quotes(t_shell *shell)
// {
// 	int		i;
// 	char	*line;
// 	int 	single_quote;

// 	i = 0;
// 	single_quote = 0;
// 	line = shell->cmd.line;
// 	while (line[i])
// 	{
// 		if (line[i] == '\'')
// 		{
// 			single_quote++;
// 			i++;
// 			while (line[i] && line[i] != '\'')
// 				i++;
// 			if(line[i] == '\'')
// 				single_quote++;
// 		}
// 		i++;
// 	}
// 	printf("print single : %d\n", single_quote); // pour check le nbr
// 	return (single_quote);
// }
// int	count_double_quotes(t_shell *shell)
// {
// 	int		i;
// 	char	*line;
// 	int 	double_quote;

// 	i = 0;
// 	double_quote = 0;
// 	line = shell->cmd.line;
// 	while (line[i])
// 	{
// 		if (line[i] == '"')
// 		{
// 			double_quote++;
// 			i++;
// 			while (line[i] && line[i] != '"')
// 				i++;
// 			if(line[i] == '"')
// 				double_quote++;
// 		}
// 		i++;
// 	}
// 	printf("print double : %d\n", double_quote); // pour check le nbr
// 	return (double_quote);
// }

// int	check_quotes(t_shell *shell)
// {
//     // printf("print single : %d\n", count_quotes(shell, "")); // pour check le nbr
// 	if (count_quotes(shell, '\'') % 2 != 0)
// 		return (1);
// 	if (count_quotes(shell, '"') % 2 != 0)
// 		return (1);	
// 	return (0);
// }

// void	last_token(t_shell	*shell, t_token *current, int *j, int *i)
// {
// 	char *value;

// 	value = current->value;
// 	if (ft_isoperator(value[j - 1]))
// 	{
// 		return ;
// 	}
// 	i = j;
// 	while(!ft_isoperator(value[j]) && j > 0)
// 		j--;
// 	if (j < i)
// 	{
// 		create_insert_token(shell, i, (j + 1), current);
// 	}
// }

// char	*create_var(const char *name, const char *value)
// {
// 	int		len;
// 	char	*var;

// 	len = ft_strlen(name) + ft_strlen(value) + 2; // car '=' et '\0'
// 	var = malloc(len);
// 	if (!var)
// 		return (NULL);
// 	ft_strlcpy(var, name, len);
// 	ft_strlcat(var, "=", len);
// 	ft_strlcat(var, value, len);
// 	return(var);
// }







// fonction qui va verifier et enregistrer au besoin la line dans la var_value
// ********* en cours ne pas juger merci ********
// void	expand_var(t_shell *shell, t_token *token)
// {
// 	int		i;
// 	int		j;
// 	int		size_new_v;
// 	char	*value;
// 	char	*rec_var;

// 	value = token->value;
// 	i = 0;
// 	while (value[i])
// 	{
// 		j = i;
// 		while (value[i] && value[i] != '$' && value[i] != '"')
// 		{
// 			if (value[i] == '\'')
// 				find_next_quote('\'', value, &i);
// 			else
// 				i++;
// 		}
// 		if (value[i] == '$' || value[i] == '\0')
// 		{
// 			if (i > j)
// 				token->var_value = join_free(token->var_value, &value[j], (i - j));
// 			if	(value[i] == '\0')
// 				return;
// 			i++;
// 			j = i;
// 			while (value[i] != '$' && value[i] && !ft_isquote(value[i])
// 				&& !ft_isspace(value[i])) 
// 				i++;
// 			if (var_exist(shell->cmd.envp_copy, &value[j], (i - j)) == TRUE)
// 			{
// 				rec_var = recup_var(shell->cmd.envp_copy, &value[j], (i - j));
// 				size_new_v = ft_strlen_plusplus(rec_var);
// 				token->var_value = join_free(token->var_value, rec_var, size_new_v);
// 			}
// 		}
// 		else if (value[i] == '"')
// 		{
// 			if (i > j)
// 				token->var_value = join_free(token->var_value, &value[j], (i - j));
// 			i++;
// 			j = i;
// 			while (value[i] != '$' && value[i] && value[i] != '"') 
// 				i++;
// 			if (i > j)
// 				token->var_value = join_free(token->var_value, &value[j], (i - j));
// 			if(value[i] == '$')
// 			{
// 				if (var_exist(shell->cmd.envp_copy, &value[j], (i - j)) == TRUE)
// 				{
// 					rec_var = recup_var(shell->cmd.envp_copy, &value[j], (i - j));
// 					size_new_v = ft_strlen_plusplus(rec_var);
// 					token->var_value = join_free(token->var_value, rec_var, size_new_v);
// 				}
// 			}
// 		}
// 		printf("test : %s\n", token->var_value);
// 	}
// }



// void	delete_quotes_var_value(t_token *token)
// {
// 	int	i;
// 	int	j;
// 	char *new_line;

// 	i = 0;
// 	new_line = NULL;
// 	while (token->var_value[i])
// 	{
// 		j = i;
// 		while (token->var_value[i] && !ft_isquote(token->var_value[i]))
// 			i++;
// 		if	(token->value[i] == '\0')
// 			return;
// 		if (i > j)
// 			new_line = join_free(new_line, &token->value[j], (i - j));
// 		if (ft_isquote(token->var_value[i]) == TRUE)
// 		{
// 			j = i + 1;
// 			find_next_quote(token->var_value[i], token->var_value, &i);
// 			new_line = join_free(new_line, &token->var_value[j], (i - j - 1));
// 			i++;
// 		}
// 		else
// 			return ;
// 	}
// 	free(token->var_value);
// 	token->var_value = new_line;
// }


// char	**extract_tab(char **av, int *i)
// {
// 	int count;
// 	char **new_av;

// 	count = 0;
// 	while (ft_strncmp(av[*i], "|", 1) != 0 && av[*i])
// 	{
// 		count ++;
// 		(*i)++;
// 	}
// 	new_av = malloc_tab(count);
// 	fill_tab(new_av, av, count);
// 	if (ft_strncmp(av[*i], "|", 1) == 0)
// 		(*i)++;
// 	return (new_av);
// }

// char	**delet_redir(char **av)
// {
// 	char	**new_tab;
// 	int		len;
// 	int		i;
// 	int		j;

// 	len = ft_tablen(av);
// 	new_tab = malloc(sizeof(char*) * len);
// 	if (!new_tab)
// 		return (NULL);
// 	i = 0;
// 	j = 0;
// 	while (av[i]) // pour tt copier sauf la var a suppr
// 	{
// 		if (is_redir(av[i]) == FALSE)
// 			new_tab[j++] = ft_strdup(av[i]);
// 		i++;
// 	}
// 	new_tab[j] = NULL;
// 	return (new_tab);
// }


/* va mettre en place les infos a chaque fois qu on voit un > < >> */
/************* seems ok pas vraiment ok ******************/
// void	set_redir_file(t_shell *shell, char **av)
// {
// 	int i;
// 	int	j;

// 	i = ft_tablen(av) - 1;
// 	j = shell->executor.nb_redir;
// 	shell->executor.nb_redir_wip = shell->executor.nb_redir;
// 	while (i > 0 && j > 0)
// 	{
// 		if (is_redir(av[i]) == TRUE)
// 			{
// 				j--;
// 				if (j == 0)
// 					break;
// 			}
// 		i--;
// 	}
// 	shell->executor.nb_redir_wip--;
// 	if (shell->executor.redir_file != NULL)
// 		free(shell->executor.redir_file);
// 	if (av[i + 1])
// 		shell->executor.redir_file = ft_strndup(av[i + 1], ft_strlen(av[i + 1]));
// 	else
// 		shell->executor.redir_file = NULL;
// 	set_redir_type(shell, av[i]);
// 	shell->executor.redir_av = set_redir_av(shell->executor.av);
// }


// void	set_redir_file(t_shell *shell, char **av)
// {
// 	int i;
// 	int	j;

// 	i = ft_tablen(av) - 1;
// 	j = shell->executor.nb_redir;
// 	shell->executor.nb_redir_wip = shell->executor.nb_redir;
// 	while (i > 0 && j > 0)
// 	{
// 		if (is_redir(av[i]) == TRUE)
// 			{
// 				j--;
// 				if (j == 0)
// 					break;
// 			}
// 		i--;
// 	}
// 	shell->executor.nb_redir--;
// 	if (shell->executor.redir_file != NULL)
// 		free(shell->executor.redir_file);
// 	if (av[i + 1])
// 		shell->executor.redir_file = ft_strndup(av[i + 1], ft_strlen(av[i + 1]));
// 	else
// 		shell->executor.redir_file = NULL;
// 	set_redir_type(shell, av[i]);
// 	shell->executor.redir_av = delete_redir(av);
// }

// char	**delet_redir(char **av)
// {
// 	char	**new_tab;
// 	int		len;
// 	int		i;
// 	int		j;

// 	len = ft_tablen(av);
// 	new_tab = malloc(sizeof(char*) * len);
// 	if (!new_tab)
// 		return (NULL);
// 	i = 0;
// 	j = 0;
// 	while (av[i]) // pour tt copier sauf la var a suppr
// 	{
// 		if (is_redir(av[i]) == FALSE)
// 			new_tab[j++] = ft_strdup(av[i]);
// 		i++;
// 	}
// 	new_tab[j] = NULL;
// 	return (new_tab);
// }







// IJ origine
// void	execution(t_shell *shell)
// {
// 	nb_pipe(shell, shell->tlist.head);
// 	create_av(shell, shell->tlist.head);
// 	if (!shell || !shell->executor.av || !shell->executor.av[0])
// 		return ;
// 	if (is_builtin(shell->executor.av[0]) == TRUE)
// 		exec_builtin(shell);
// 	else
// 	{
// 		if (shell->executor.nb_pipe > 0)
// 			exec_pipe(shell);
// 		else
// 			exec_path(shell, shell->executor.av[0], shell->executor.av,
// 				shell->cmd.envp_exp);
// 	}
// }

// void	fill_tab(char **new_tab, char**old_tab, int len)
// {
// 	int i;

// 	i = 0;
// 	while (i < len)
// 	{
// 		new_tab[i] = ft_strdup(old_tab[i]);
// 		if (new_tab[i] == NULL)
// 			free_mid_tab(new_tab, i);
// 		i++;
// 	}
// }


// char **delete_redir(char **av)
// {
// 	int count;
// 	int	i;
// 	int	j;

// 	count = 0;
// 	i = 0;
// 	while (av[i])
// 	{
// 		if (is_redir(av[i]))
// 			i += 2; // skip redir and filename
// 		else
// 		{
// 			count++;
// 			i++;
// 		}
// 	}

// 	char **new_tab = malloc(sizeof(char *) * (count + 1));
// 	if (!new_tab)
// 		return (NULL);

// 	i = 0;
// 	j = 0;
// 	while (av[i])
// 	{
// 		if (is_redir(av[i]))
// 			i += 2;
// 		else
// 			new_tab[j++] = ft_strdup(av[i++]);
// 	}
// 	new_tab[j] = NULL;
// 	return new_tab;
// }

// char	**delete_redir(char **av)
// {
// 	char	**new_tab;
// 	int		i;

// 	i = 0;
// 	while (!is_redir(av[i]))
// 		i++;
// 	new_tab = malloc(sizeof(char*) * (i + 1));
// 	if (!new_tab)
// 		return (NULL);
// 	i = 0;
// 	while (!is_redir(av[i]))
// 	{
// 		new_tab[i] = ft_strdup(av[i]);
// 		i++;
// 	}
// 	new_tab[i] = NULL;
// 	return (new_tab);
// }

// void create_redir_av(t_shell *shell)
// {
// 	printf("hello darkness my old friend\n");
// 	shell->executor.redir_av = shell->executor.av;

// 	if (shell->executor.nb_redir > 0)
// 	{
// 		shell->executor.redir_av = delete_redir(shell->executor.redir_av);
// 	}
// }

// cat < file.txt -> file.txt devient stdin
// echo hello > out.txt -> ecrit "hello" das out.txt (ecrase)
// echo again >> out.txt -> ajoute "again" a la fin de out.txt