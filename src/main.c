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
	cpy_envp(&shell, envp);
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
		check_error(&shell); // a faire avant le parsing
		token_blank(&shell);
		print_token(shell.tlist.head, printf);
		//parsing
		free (shell.cmd.line);
	}
	
	// CLEAR HISTORY ?? 
	// FONCTION FREE ALL A LA FIN 
	return (0);
}
