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
	//t_shell	shell;
	char	*line;

	(void)ac;
	(void)av;
	if (!envp || !envp[0])
		return (1); // mettre une faute ou whatever
	shell.cmd->envp_copy = cpy_tab(envp);
	// init_all(&shell); 
	setup_signals();
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
	
	// CLEAR HISTORY ?? 
	// FONCTION FREE ALL A LA FIN 
	return (0);
}
