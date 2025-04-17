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
	if (!envp || !envp[0])
		return (1); // mettre une faute ou whatever
	shell.cmd->envp_copy = cpy_tab(envp);
	// init_all(&shell); 
	while (1)
	{
		shell.cmd->line = readline(PROMPT);
		if (!shell.cmd->line)
		{
			printf("exit");
			break ;
		}
		if (*shell.cmd->line)
			add_history(shell.cmd->line);
		// faire des trucs ici ...
		free (shell.cmd->line);
	}
	// gestion de signal pour ctrl d ou c ??????
	// CLEAR HISTORY ?? 
	// FONCTION FREE ALL A LA FIN 
	return (0);
}
