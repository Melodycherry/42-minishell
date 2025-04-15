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
	t_shell	shell;
	char	*line;

	//initialiser la structure et sous structure de shell
	init_all(&shell); 
	// fonction pour faire le env?? 
	while (1)
	{
		line = readline("Minishell CDD > "); // CDD = Codeuses Du Dimanche ;)
		if (!line)
			//fonction free ?? free all ? et on exit ? 
		if (*line)
			add_history(line);
		// faire des trucs ici ...
		free (line);
	}
	
	// ABOVE ↑↑↑
	// loop infinie
	// envoie readline
	// If pas de ligne : on ne passe pas par addhistory ou EXIT //demander a PDEMONT
	// If ligne : addhistory
	// free readline

	// gestion de signal pour ctrl d ou c ??????
	
	// CLEAR HISTORY ?? 
	// FONCTION FREE ALL A LA FIN 
	return (0);
}