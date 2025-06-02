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
void create_av(t_shell *shell, t_token *current)
{
	int 	i;
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

// fonction qui creer un tableau de pathS avec les differents path
// ********* a tester *******
void create_path(t_shell *shell, char **envp)
{
	char **paths;
	int i; 
	
	i = 0;

	while (ft_strncmp(envp[i], "PATH", 4) != 0)
		i++;
	paths = ft_split(envp[i], ':');

	shell->executor.paths = paths;
}