/*****************************************************************************/
/*                                                                           */
/*                                                                           */
/*                                                                           */
/*                                                                           */
/*      LES CODEUSES DU DIMANCHE                                             */
/*      FONT UN MINISHELL                                                    */
/*                                                                           */
/*                                                                           */
/*                                                                           */
/*****************************************************************************/

#include "minishell.h"

// Check si la variable existe dans l'export
// ***** a tester ******
t_bool var_exist(char **envp, const char *var_env)
{
	int		i;
	int		len;
	char	*equal_sign;

	i = 0;
	len = ft_strlen(var_env);
	while (envp[i])
	{
		equal_sign = ft_strchr(envp[i], '=');
		if (equal_sign)	
			if (ft_strncmp(envp[i], var_env, (int)(equal_sign - envp[i][0])) == 0 && (envp[i][len] == '='))
				return (TRUE);
		else 
			if (envp[i][len] == '\0')
				return (TRUE);
		i++;
	}
	return(FALSE);
}

// retourne la position dans le tableau env
// ********* a tester *********
int	pos_var_env(char **envp, char *var_env)
{
	int		i;
	int		len;
	char	*equal_sign;

	i = 0;
	len = ft_strlen(var_env);
	while (envp[i])
	{
		equal_sign = ft_strchr(envp[i], '=');
		if (equal_sign)	
			if (ft_strncmp(envp[i], var_env, (int)(equal_sign - envp[i][0])) == 0 && (envp[i][len] == '='))
				return (i);
		else 
			if (envp[i][len] == '\0')
				return (i);
		i++;
	}
	return(i);
}

// fonction de refactorisation qui va verifier l existance d une variable dans le env, recupere sa position
// la remplace si existante ou l ajoute sinon
// ****** a tester *********
void	insert_env_export(t_shell *shell, char *value, char **tab, t_bool is_export)
{
	int	index;

	index = 0;
	if (var_exist(tab, value))
		{
			index= pos_var_env(tab, value);	
			free(tab[index]);
			tab[index] = strndup(value, ft_strlen(value));
		}
	else
		put_in_env_export(shell, tab, value, is_export);
}

//mettre des information dans le envp_export et potientiellement dans le envp_copy
//********** a tester ********/
void	set_env(char *value, int to_tab, t_shell *shell)
{
	if (to_tab == TO_EXPORT)
		insert_env_export(shell, value, shell->cmd.envp_exp, TRUE);
	else if (to_tab == TO_BOTH)
	{
		insert_env_export(shell, value, shell->cmd.envp_exp, TRUE);
		insert_env_export(shell, value, shell->cmd.envp_copy, FALSE);
	}
	else 
		return (printf("WTF GUUURL\n"));
}

// fonction qui retourne la valeur de la variable d expendion "path"
//pas de modif du tableau donc pas de malloc - chercher des inos
// $USR='Melo" -> prend USER return Melo
//char *get_env(char *path)
//{
//	;
//}

//COMMENT HYGIE
//fonction qui va ajouter une nouvelle variable d'expansion dans le tableau
// realloc du tableau pcq on rajoute 1
//int set_env(const char *name, const char *value, int overwrite)
// {
// 	// copie du tableau ou on ajoue le nouveau ARG
// 	// remvoie un int ou un char **
// 	// change le tableau dans shell.cmd.env_cpy
// 	// USER2=Melomelo
// 	;
// }

// COMMENT MELO
// Fonction qui va ajouter une nouvelle variable d'expansion dans le tableau
// d'abord check si elle existe
// -> faire fonction var_exist ? ( OK ? )
// if yes, on la modifie
// if existe pas, on la creer 
// -> fonction create_var (OK ? ))
// a stocker dans le tableau de envp ( + export ? ) 
// donc realloc tableau pour rajouter ? 
// et free ancien tableau ? 