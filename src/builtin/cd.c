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
void	builtin_cd()
{
	// check si pas plus de 2 arg sinon "too many arguments"

}

// check chdir ( change directory ) 
// check old_pwd ( a coder ) et aussi update the pwd