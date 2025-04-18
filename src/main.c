/*******************************************************************************/
/*                                                                             */
/*                                                                             */
/*                                                                             */
/*                                                                             */
/*      LES CODEUSES DU DIMANCHE                                               */
/*      FONT UN MINISHELL                                                      */
/*                                                                             */
/*                                                                             */
/*                                                                             */
/*******************************************************************************/

#include "minishell.h"

int	main(int ac, char **av, char **envp)
{
	//t_shell	shell;
	char	*line;

	(void)ac;
	(void)av;
	(void)envp; // pour l instant
	//initialiser la structure et sous structure de shell
	// init_all(&shell); 
	// fonction pour faire le env?? 
	setup_signals();
	while (1)
	{
		line = readline(PROMPT);
		if (!line)
			{
				printf("exit");
				break;
			}
		if (*line)
			add_history(line);
		// faire des trucs ici ...
		free (line);
	}
	
	// CLEAR HISTORY ?? 
	// FONCTION FREE ALL A LA FIN 
	return (0);
}