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

// fonction qui va va transformer la liste chainee en tableau
// ******* testee et fonctionnelle ********
void	create_av(t_shell *shell, t_token *current)
{
	int		i;
	char	**av;

	i = 0;
	av = malloc(sizeof(char *) * (shell->tlist.token_cnt + 1));
	if (!av)
		return (perror("malloc\n"));
	while (i < shell->tlist.token_cnt)
	{
		if (current->type == T_ARG)
			av[i] = ft_strdup(current->var_value);
		else
			av[i] = ft_strdup(current->value);
		current = current->next;
		i++;
	}
	av[i] = NULL;
	shell->executor.av = av;
}

// // fonction qui creer un tableau de pathS avec les differents path
// // ********* seems good *******
void	create_path(t_shell *shell, char **envp)
{
	int	i;

	i = 0;
	while (envp[i] && ft_strncmp(envp[i], "PATH=", 5) != 0)
		i++;
	if (envp[i])
		shell->executor.paths = ft_split(envp[i] + 5, ':');
	else
		shell->executor.paths = NULL;
}

// va checker si le path existe via le access sur le while du pathS
// ***** en cours, focntionne dans cet etat *****
char	*right_path(char **paths, char *cmd)
{
	int		i;
	char	*path;

	i = 0;
	while (paths[i])
	{
		path = strjoin_path(paths[i], cmd);
		if (!access(path, F_OK))
		{
			if (!access(path, X_OK))
				return (path);
			//else
			// 	gestion d erreur
		}
		free_ptr((void **)&path);
		i++;
	}
// gestion d erreur
	return (NULL);
}

// va checker l existance d un / -> si cest absolative (absolu ou relative)
// faire les gestion des  edges cases : 
// juste des.. ou juste des / ou what // faire jour de la correction loool
// ******* seems good ***********
t_bool	is_absolative(char *str)
{
	if (ft_strchr(str, '/'))
		return (TRUE);
	return (FALSE);
}

// //join qui malloc et renvoie le path + / + cmd
// // *** seems to work., ya un malloc donc pas oublier de free :) ***
char	*strjoin_path(char *s1, char *s2)
{
	char	*dest;
	char	*tmp;

	tmp = ft_strjoin(s1, "/");
	if (!tmp)
		return (NULL);
	dest = ft_strjoin(tmp, s2);
	free_ptr((void **)&tmp);
	return (dest);
}
