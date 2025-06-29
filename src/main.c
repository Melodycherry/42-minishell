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
	token_operator(shell, shell->tlist.head);
	//premiere definition
	token_typedef(shell->tlist.head);
	//definition si var env good
	// revoir la fonction et l outcome 
	// if (is_token_error(shell->tlist.head, shell) == 1)
	// 	printf("GUUUUURL ITS NOT GOOD\n");
	// else
	// 	printf("NOICE\n");
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
	char	*file;
	char	*stri;
	int		i;

	(void)ac;
	(void)av;
	init_all(&shell);
	cpy_envp(&shell, envp);
	setup_signals();
	while (1)
	{
		shell.cmd.line = readline(PROMPT);
		if (!shell.cmd.line)
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
					return (1); // faire une gestion d erreur ici
				file = ft_strjoin("/tmp/ms_hd_", stri);
				if (!file)
					return (1); // faire une gestion d erreur ici
				unlink(file);
				free_ptr((void **)&stri);
				i++;
			}
			shell.executor.index_file_heredoc = 0; // reinitialise le nbr de heredoc
			free_tab(&shell.executor.av);
			free_tab(&shell.executor.redir_av);
			free_tab(&shell.executor.pipe_av);
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
	free_all(&shell);
	free_token_list(&shell);
	return (0);
}
