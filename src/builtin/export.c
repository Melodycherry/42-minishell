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

void	print_export(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		printf("declare -x %s\n", tab[i]);
		i++;
	}
}
void	handle_export(t_shell *shell)
{
	// if export tout seul :
	// -> print le tableau dans l'ordre ASCII avec "declare -x "
	bubble_tab(shell->cmd.envp_copy);
	print_export(shell->cmd.envp_copy);
	
	// if export + variable sans $ ou mot
	// -> met la VAR ou WORD dans env -> set_env -----> value="value_arg"

}

// export + old ARG -> rien
// export + new ARG -> set dans env value="value_arg" /!\ de mettre des guillemets
// export + mot -> met le mot SANS GUILLEMET dans env


