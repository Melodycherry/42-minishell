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
	init_list(&shell);
	
	// envoie readlin
	while (1)
		line = readline(PROMPT);

	// If pas de ligne : on ne passe pas par addhistory ou EXIT //demander a PDEMONT
	// If ligne : addhistory
	// free readline
	// gestion de signal pour ctrl d ou c ??????
	// loop infinie

	return (0);
}