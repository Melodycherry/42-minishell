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
 * cd — change the working directory
 * The cd utility shall change the working directory of the current
    shell execution environment (see Section 2.12, Shell Execution
    Environment) by executing the following steps in sequence.
 */
void	builtin_cd(t_shell *shell)
{
	(void)shell;
	// check si pas plus de 2 arg sinon "too many arguments"
	//if (ac > 2)
		//return (perror("Too many arguments"));
}
void	update_pwd()
{

}
void	old_pwd()
{
	
}

// check chdir ( change directory ) 
// check old_pwd ( a coder ) et aussi update the pwd