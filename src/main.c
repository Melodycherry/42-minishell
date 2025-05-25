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
	expansion(shell);
	
	// test impression
	print_token(shell->tlist.head, printf);
	// print_token2(shell->tlist.head, printf);
	// print_token3(shell->tlist.head, printf);
	
	// revoir la fonction et l outcome 
	if (is_token_error(shell->tlist.head, shell) == 1)
		printf("GUUUUURL ITS NOT GOOD\n");
	else
		printf("NOICE\n");
	
}

int	main(int ac, char **av, char **envp)
{
	t_shell	shell;

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
			add_history(shell.cmd.line);
		parsing(&shell);
		free(shell.cmd.line);
		free_token_list(&shell);
	}
	free(shell.cmd.line);
	rl_clear_history();
	free_tab(&shell, shell.cmd.envp_copy);
	free_tab(&shell, shell.cmd.envp_exp);
	free_token_list(&shell);
	return (0);
}
