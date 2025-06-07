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
void	old_pwd()
{
	// OLDPWD = ancien repertoire ( on doit faire getcwd avant chdir)
}

void	update_pwd()
{
	//PWD = nouveau repertoire  on doit faire getcwd avant chdir)
}
// check chdir ( change directory ) 
// int chdir(const char *path) -> retourne 0 si ok, -1 si erreur 
// check old_pwd ( a coder ) et aussi update the pwd

// on doit sauvegarder getcwd(NULL, 0) avant chdir
// appeler chdir(path)
// si marche appeler getcwd again, et modif les valeur de PWD et aussi OLDPWD dans l'env 

// on doit faire une fonction pour recup variable d'env ? get_env_value ? 
// !!! penser a free ! oldpwd et pwd 