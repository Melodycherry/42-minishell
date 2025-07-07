/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_tab.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlichten <hlichten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 20:34:16 by hlichten          #+#    #+#             */
/*   Updated: 2025/07/07 20:34:18 by hlichten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_mid_tab(t_shell *shell, char ***tab, int i)
{
	if (!tab && !*tab)
		return ;
	while (i > 0)
	{
		i--;
		free_ptr((void **)&((*tab)[i]));
	}
	free(*tab);
	*tab = NULL;
	unfructuous_malloc(shell);
}

void	free_tab(char ***tab)
{
	int	i;

	i = 0;
	if (!tab || !*tab)
		return ;
	while ((*tab)[i])
	{
		free_ptr((void **)&((*tab)[i]));
		i++;
	}
	free(*tab);
	*tab = NULL;
}
