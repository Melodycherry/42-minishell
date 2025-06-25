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
void	parsing(t_shell *shell)
{
	// separation par espaces
	token_blank(shell);
	//separation par operateur
	token_operator(shell);
	//premiere definition
	token_typedef(shell->tlist.head);
	//definition si var env good
	// revoir la fonction et l outcome 
	if (is_token_error(shell->tlist.head, shell) == 1)
		printf("GUUUUURL ITS NOT GOOD\n");
	else
		printf("NOICE\n");
	handle_heredoc(shell);
	expansion(shell);

	// test impression
	// print_token(shell->tlist.head, printf); // pour c4ette shit d expansion
	// print_token2(shell->tlist.head, printf);
	// print_token3(shell->tlist.head, printf);
}

int	main(int ac, char **av, char **envp)
{
	t_shell	shell;
	char *file;
	char *stri;
	int i;


	(void)ac;
	(void)av;
	//premieres étapes
	init_all(&shell);
	cpy_envp(&shell, envp);
	setup_signals();
	// boucle readline -> reste la
	while (1)
	{
		shell.cmd.line = readline(PROMPT);
		if (!shell.cmd.line) //ctrl D
		{
			printf("exit");
			break ;
		}
		if (*shell.cmd.line)
		{
			add_history(shell.cmd.line);
			parsing(&shell);
			execution(&shell);
			i = 1;
			while (i <= shell.executor.nb_heredoc)
			{
				stri = ft_itoa(i);
				if (!stri)
					return 1; // faire une gestion d erreur ici
				file = ft_strjoin("/tmp/ms_hd_", stri);
				if (!file)
					return 1; // faire une gestion d erreur ici
				unlink(file);
				free_ptr((void **)&stri);
				i++;
			}
			shell.executor.index_file_heredoc = 0; // reinitialise le nbr de heredoc
			free_tab(&shell, shell.executor.av);
			free_ptr((void **)&shell.cmd.line);
			free_token_list(&shell);
			shell.executor.is_forked = FALSE;
			shell.executor.end = 0;
			shell.executor.start = 0;
		}
	}
	//free a mettre dans une fonction :) 
	free_ptr((void **)&shell.cmd.line);
	rl_clear_history();
	free_tab(&shell, shell.cmd.envp_copy);
	free_tab(&shell, shell.cmd.envp_exp);
	free_tab(&shell, shell.executor.av);
	free_tab(&shell, shell.executor.pipe_av);
	free_tab(&shell, shell.executor.paths);
	free_tab(&shell, shell.executor.redir_av);
	free_token_list(&shell);
	return (0);
}

// char	*recup_var2(char **envp, char *var_env, int len)
// {
// 	int		i;
// 	int		j;
// 	int		k;
// 	char	*equal_sign;
// 	char	*ret;

// 	i = 0;
// 	while (envp[i])
// 	{
// 		equal_sign = ft_strchr(envp[i], '=');
// 		j = (int)(equal_sign - envp[i]);
// 		if (ft_strncmp(envp[i], var_env, j) == 0 && (envp[i][len] == '='))
// 		{
// 			j++;
// 			k = j;
// 			while (envp[i][j])
// 				j++;
// 			ret = ft_strdup(&envp[i][k]);
// 			printf("var inside recup = %s\n", ret);
// 			return (ret);
// 		}
// 		i++;
// 	}
// 	return (NULL);
// }

// char *heredoc_variable_expansion(t_shell *shell, char *line)
// {
// 	char 	*tmp;
// 	char	*rec_var;
// 	int 	i;
// 	int		j;
// 	int		k = 0;

// 	j = 0;
// 	i = 0;
// 	tmp = NULL;
// 	while (line[i])
// 	{
// 		if (line[i] == '$')
// 		{
// 			if (i > j)
// 				tmp = join_free(tmp, &line[j], i - j); // text before $
// 			i++;
// 			j = i;
// 			while (line[i] && (ft_isalnum(line[i]) || line[i] == '_'))
// 				i++;
// 			if (i > j && var_exist(shell->cmd.envp_copy, &line[j], i - j))
// 			{
// 				printf("on vieent recuperer la var\n");
// 				rec_var = recup_var2(shell->cmd.envp_copy, &line[j], i - j);
// 				printf("rec_var[%d] : %s\n", k, rec_var);
// 				tmp = join_free(tmp, rec_var, ft_strlen(rec_var));
// 				printf("i[%d] : %d\n", k, i);
// 				printf("j[%d] : %d\n", k, j);
// 				printf("tmp[%d] : %s\n", k, tmp);
// 				k++;
// 			}
// 			j = i;
// 		}
// 		else
// 			i++;
// 	}
// 	if (i > j)
// 		tmp = join_free(tmp, &line[j], i - j);
// 	return tmp;
// }

	// if (var_exist(shell->cmd.envp_copy, &value[*j], (*i - *j)) == TRUE)
	// {
	// 	rec_var = recup_var(shell->cmd.envp_copy, &value[*j], (*i - *j));
	// 	token->var_value =
	// 		join_free(token->var_value, rec_var, ft_strlen_plusplus(rec_var));
	// 	(*j) = (*i);
	// }