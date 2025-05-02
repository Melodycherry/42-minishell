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
	print_export(shell->cmd.envp_copy);
	
	// if export + variable sans $ ou mot
	// si mot simple -> value
	// si mot + = + mot -> VALUE_ARG
	// -> met la VAR ou WORD dans env -> set_env -----> value="value_arg"
	// /!\ mise a jour env seulement si il y a un = meme si rien apres le = // sinon toujours dans le export
}

t_bool is_valid_var_name(t_token *token, t_shell *shell)
{
	int		i;
	char	*line;

	i = 0;
	line = token->value;
	while (line)
	{
		if (line[0] == '_' || ft_isalpha(line[0]))
			i++;
		else 
			return (FALSE, printf("bash: export: `%s': not a valid identifier", line)); //comme ctrlC
		if (line[i] == '_' || ft_isalnum(line[i]))
			i++;
		else if (line[i] == '=')
			return (TRUE);
			//creer fonction qui met dans le env_cpy + env_exp + gerer les infos apres var_value
		else if (line[i] == ' ' && line[i] == '\0')
			return (TRUE);
			//creer fonction qui met dans le env_exp
		else 
			return (FALSE, printf("bash: export: `%s': not a valid identifier", line)); //comme ctrlC		
	}
	return (TRUE);
}

void	put_in_export(void)
{
	;
}
// mettre dans envp_cpy + envp_exp la nouvelle VAR + mettre a jour le token via strndup la VAR_VALUE
void	put_in_env(void)
{
	;
}
// export + old ARG -> rien
// export + new ARG -> set dans env value="value_arg" /!\ de mettre des guillemets
// export + mot -> met le mot SANS GUILLEMET dans env


