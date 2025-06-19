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
 * exit — cause the shell to exit
 * The exit utility shall cause the shell to exit from its current
    execution environment with the exit status specified by the
    unsigned decimal integer n.  If the current execution environment
    is a subshell environment, the shell shall exit from the subshell
    environment with the specified exit status and continue in the
    environment from which that subshell environment was invoked;
    otherwise, the shell utility shall terminate with the specified
    exit status. If n is specified, but its value is not between 0 and
    255 inclusively, the exit status is undefined.
 */
// void	builtin_exit()
// {
// 	;
// }

// si exit sans arg = juste exit normal
// si arg doit etre only numeric
// donc vweerif si arg est num only sinon exit + mess d'erreur non num

// zero 0 succes
// 1 si erreur 
// si pb d'arg, code erreur 2 (pb d'option)