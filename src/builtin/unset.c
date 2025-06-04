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
 * unset — unset values and attributes of variables and functions
 * Each variable or function specified by name shall be unset.
 * Unsetting a variable or function that was not previously set shall
	not be considered an error and does not cause the shell to abort.
 */
void	builtin_unset()
{

}

// check si variable valide ( deja fait : is_valid var name)
// si pas valide : erreur
// si valide on supp la valeur
// faire une fonction pour suppr ( check fonction Hygie ?)
// re malloc -1 et recop sans la ligne 
// !! penser a faire sur export et sur envpcpy 