/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlichten <hlichten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 20:36:09 by hlichten          #+#    #+#             */
/*   Updated: 2025/07/07 20:38:31 by hlichten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

char	**cpy_tab(t_shell *shell, char **tab)
{
	int		i;
	char	**cpy_tab;

	(void)shell;
	i = 0;
	cpy_tab = malloc(sizeof(char *) * (ft_tablen(tab) + 1));
	if (!cpy_tab)
		unfructuous_malloc(shell);
	while (i < ft_tablen(tab))
	{
		cpy_tab[i] = ft_strdup(tab[i]);
		if (cpy_tab[i] == NULL)
			free_mid_tab(shell, &cpy_tab, i);
		i++;
	}
	cpy_tab[i] = 0;
	return (cpy_tab);
}

char	**init_envp_copy(t_shell *shell, char **tab)
{
	int		i;
	char	**cpy_tab;

	(void)shell;
	i = 1;
	cpy_tab = malloc(sizeof(char *) * (ft_tablen(tab) + 2));
	if (!cpy_tab)
		unfructuous_malloc(shell);
	cpy_tab[0] = ft_strdup("?=0");
	while (i < ft_tablen(tab + 1))
	{
		cpy_tab[i] = ft_strdup(tab[i]);
		if (cpy_tab[i] == NULL)
			free_mid_tab(shell, &cpy_tab, i);
		i++;
	}
	cpy_tab[i] = 0;
	return (cpy_tab);
}

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
