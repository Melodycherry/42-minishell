/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlichten <hlichten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 20:33:10 by hlichten          #+#    #+#             */
/*   Updated: 2025/07/07 20:33:12 by hlichten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	validate_exit_arg(t_shell *shell, char **av, int *exit_status);

int	builtin_exit(t_shell *shell, char **av)
{
	char	*str_exit_status;
	int		exit_status;

	if (av[1])
		validate_exit_arg(shell, av, &exit_status);
	else
	{
		str_exit_status = recup_var(shell->cmd.envp_copy, "?", 1);
		exit_status = ft_atoi(str_exit_status);
	}
	ft_putendl_fd("exit", STDERR_FILENO);
	free_all(shell);
	exit(exit_status);
}

static void	validate_exit_arg(t_shell *shell, char **av, int *exit_status)
{
	int	i;

	i = 0;
	while (av[1][i])
	{
		if (!ft_isdigit(av[1][i]))
		{
			ft_putendl_fd("exit\nNeed numeric argument", STDERR_FILENO);
			free_all(shell);
			exit(2);
		}
		i++;
	}
	if (av[2])
	{
		ft_putendl_fd("exit\nToo many arguments", STDERR_FILENO);
		free_all(shell);
		exit(1);
	}
	*exit_status = ft_atoi(av[1]);
}
