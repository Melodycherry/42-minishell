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

// fonction pour connaitre le nb de row d un tableau
// **** testée ca a l air ok *****
int	ft_tablen(char **tab)
{
	int	i;

	i = 0;
	if (!tab)
		return (0);
	while (tab[i])
		i++;
	return (i);
}

// fonction pour copier le tableau des env recu dans cmd 
// **** testée ca a l air ok *****
char	**cpy_tab(char **tab)
{
	int		i;
	char	**cpy_tab;

	i = 0;
	cpy_tab = malloc(sizeof(char *) * (ft_tablen(tab) + 1));
	if (!cpy_tab)
		return (NULL);
	while (i < ft_tablen(tab))
	{
		cpy_tab[i] = ft_strdup(tab[i]);
		if (cpy_tab[i] == NULL)
			free_mid_tab(cpy_tab, i);
		i++;
	}
	cpy_tab[i] = 0;
	return (cpy_tab);
}

//fonction qui met l'envp dans l'ordre alphabetique
// **** testée ca a l air ok *****
void	bubble_tab(char **tab)
{
	int		i;
	int		j;
	int		size;
	char	*tmp;

	i = 0;
	size = ft_tablen(tab) - 1;
	while (i < size)
	{
		j = 0;
		while (j < size - i)
		{
			if (strcmp(tab[j], tab[j + 1]) > 0)
			{
				tmp = tab[j];
				tab[j] = tab[j + 1];
				tab[j + 1] = tmp;
			}
			j++;
		}
		i++;
	}
}

void	cpy_envp(t_shell *shell, char **envp)
{
	if (!envp || !envp[0])
		shell->cmd.envp_copy = malloc(sizeof(char *) * (ft_tablen(envp)) + 1);
	else
	{
		shell->cmd.envp_copy = cpy_tab(envp);
		shell->cmd.envp_exp = cpy_tab(envp);
		bubble_tab(shell->cmd.envp_exp);
	}
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
		return ;
}
