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

// // fonction qui retourne la valeur de la variable d expendion "path"
// //pas de modif du tableau donc pas de malloc - chercher des inos
// // $USR='Melo" -> prend USER return Melo
// char *get_env(char *path)
// {
// 	;
// }

//COMMENT HYGIE
// //fonction qui va ajouter une nouvelle variable d'expansion dans le tableau
// // realloc du tableau pcq on rajoute 1
// int set_env(const char *name, const char *value, int overwrite)
// {
// 	// copie du tableau ou on ajoue le nouveau ARG
// 	// remvoie un int ou un char **
// 	// change le tableau dans shell.cmd.env_cpy
// 	// USER2=Melomelo
// 	;
// }

//COMMENT MELO
//Fonction qui va ajouter une nouvelle variable d'expansion dans le tableau
//d'abord check si elle existe
// -> faire fonction var_exist ? ( OK ? )
// if yes, on la modifie
// if existe pas, on la creer 
// -> fonction create_var (OK ? ))
// a stocker dans le tableau de envp ( + export ? ) 
// donc realloc tableau pour rajouter ? 
// et free ancien tableau ? 

// int set_env(t_shell *shell, const char *name, const char *value, int overwrite)
// {
// 	char	*new_var;
// 	int		i;

// 	if (var_exist(shell->cmd.envp_copy, name) == TRUE)
// 	{
// 		// overwrite ??
// 		i = 0;
// 		// il faut modif la var deja la 
// 		while (shell->cmd.envp_copy[i])
// 		{
// 			if (ft_strncmp(shell->cmd.envp_copy[i], name, ft_strlen(name)) == 0 &&
// 			shell->cmd.envp_copy[i][ft_strlen(name)] == '=')
// 			{
// 				// on va free ancienne var
// 				new_var = create_var(name, value);
// 				// remplace la var dans le envp cpy
// 				return (1); // ??
// 			}
// 			i++;
// 		}
// 	}
// 	else
// 	{
// 		// ajout nouvelle variable : 
// 		// il faut compter la longueur du envp ? nombre d'entree ? -> tablen deja fait 
// 		// faire new_env ? update ? avec entree supplementaire 
// 		// ou realloc ? quelle diff ? 
// 		// cpy ancien envp
// 		// create new var
// 		// ajout new var
// 		// free ancien envp 
// 	} 
// }
// // Check si la variable existe dans l'export
// // a tester
// t_bool	var_exist(t_shell *shell, const char *name)
// {
// 	int	i;
// 	int	len;

// 	i = 0;
// 	len = ft_strlen(name);
// 	while (shell->cmd.envp_exp[i])
// 	{
// 		if (ft_strncmp(shell->cmd.envp_exp[i], name, len) == 0
// 			&& (shell->cmd.envp_exp[i][len] == '='
// 				|| shell->cmd.envp_exp[i][len] == '\0'))
// 			return (TRUE);
// 		i++;
// 	}
// 	return(FALSE);
// }

// char	*create_var(const char *name, const char *value)
// {
// 	int		len;
// 	char	*var;

// 	len = ft_strlen(name) + ft_strlen(value) + 2; // car '=' et '\0'
// 	var = malloc(len);
// 	if (!var)
// 		return (NULL);
// 	ft_strlcpy(var, name, len);
// 	ft_strlcat(var, "=", len);
// 	ft_strlcat(var, value, len);
// 	return(var);

// }

// //faire un unset ??
// // int	unset_env()
// // {
// // 	return (0);
// // }