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

// fonction pour copier le tableau des env recu dans cmd 
// **** testée ca a l air ok *****
char	**init_envp_copy(char **tab)
{
	int		i;
	char	**cpy_tab;

	i = 1;
	cpy_tab = malloc(sizeof(char *) * (ft_tablen(tab) + 2));
	if (!cpy_tab)
		return (NULL);
	cpy_tab[0] = ft_strdup("?=0");
	while (i < ft_tablen(tab + 1))
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
			if (ft_strcmp(tab[j], tab[j + 1]) > 0)
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
