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
	init_all(&shell);
	cpy_envp(&shell, envp);
	//print_export(shell.cmd.envp_exp);
	setup_signals();
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
		token_blank(&shell);
		token_operator(&shell);
		token_typedef(shell.tlist.head);
		check_var_env(&shell, shell.tlist.head);
		print_token(shell.tlist.head, printf);
		print_token2(shell.tlist.head, printf);
		if (is_token_error(shell.tlist.head, &shell) == 1)
			printf("GUUUUURL ITS NOT GOOD\n");
		else
			printf("NOICE\n");
		//parsing
		free(shell.cmd.line);
		free_token_list(&shell);
	}
	// CLEAR HISTORY ?? 
	// FONCTION FREE ALL A LA FIN 
	return (0);
}
