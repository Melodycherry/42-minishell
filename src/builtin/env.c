/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlichten <hlichten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 20:33:13 by hlichten          #+#    #+#             */
/*   Updated: 2025/07/07 20:33:15 by hlichten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_tab_env(char **tab);

int	builtin_env(t_shell *shell, char **av)
{
	if (!*shell->cmd.envp_copy)
	{
		ft_putendl_fd("No environnement", STDERR_FILENO);
		return (0);
	}
	if (av[1] && av[1][0] == '-')
	{
		ft_putendl_fd("Invalid option", STDERR_FILENO);
		return (2);
	}
	if (av[1])
	{
		ft_putendl_fd("Too many arguments", STDERR_FILENO);
		return (1);
	}
	print_tab_env(shell->cmd.envp_copy);
	return (0);
}

static void	print_tab_env(char **tab)
{
	int	i;

	i = 1;
	while (tab && tab[i])
	{
		printf("%s\n", tab[i]);
		i++;
	}
}
