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

int	main(int ac, char **av, char **envp)
{
	t_shell	shell;

	(void)ac;
	(void)av;
	(void)envp;
	//cpy_envp(&shell, envp);
	init_all(&shell);
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
		add_history(shell.cmd.line);
		// if (check_error(&shell))// a faire avant le parsing
		// 	continue ; 
		token_blank(&shell);
		print_token(shell.tlist.head, printf);
		//parsing
		free (shell.cmd.line);
		free_token_list (&shell); //probleme ici
	}
	// CLEAR HISTORY ?? 
	// FONCTION FREE ALL A LA FIN 
	return (0);
}
