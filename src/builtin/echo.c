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

/** 
 * echo – write arguments to the standard output
 * The echo utility writes any specified operands, separated by single blank (‘ ’) characters
    and followed by a newline (‘\n’) character, to the standard output.
    The following option is available:
    -n    Do not print the trailing newline character.
 */
void	builtin_echo(t_shell *shell)
{
	char **av;
	int i;

	av = shell->executor.av;
	i = 0;
	
	// ici s'occuper de cette merde d'option

	while ( av[i])
	{
		printf("%s", av[i]);
		if (av[i + 1])
			printf(" ");
		i++;
	}
	// if ( on a une option qui est valide)
	// printf("'\n");
}

// attention au -n 
// verif de 1 ou plusieurs : -n -n -n -nnnnnm

// faire qqch comme int is_option_n() ou un bool 
// si -n : return 0
// si nnn : return 0
// sinon return 1

// tant qu-ily a des arg on print
// si un arg apres ajout de " "
// car doit etre separe par espace sauf le dernier 

// faire un bool avec if newline, print \n ??