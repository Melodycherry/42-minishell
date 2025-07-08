/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlichten <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 20:33:19 by hlichten          #+#    #+#             */
/*   Updated: 2025/07/08 00:42:46 by hlichten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_bool	is_flag_n(char *str);
static void		print_echo(char **av, int *i);
static int		print_flag_n(t_shell *shell, char **av, int *i);

int	builtin_echo(t_shell *shell, char **av, t_bool is_pipe)
{
	int	i;

	if (shell->executor.redir_av)
		av = shell->executor.redir_av;
	else if (is_pipe)
		av = shell->executor.pipe_av;
	else
		av = shell->executor.av;
	i = 1;
	if (print_flag_n(shell, av, &i) == 2)
		return (2);
	if (shell->builtin.is_echo_n == TRUE)
	{
		while (av[i])
			print_echo(av, &i);
	}
	else
	{
		while (av[i])
			print_echo(av, &i);
		printf("\n");
	}
	return (0);
}

static void	print_echo(char **av, int *i)
{
	printf("%s", av[*i]);
	if (av[*i + 1])
		printf(" ");
	(*i)++;
}

static int	print_flag_n(t_shell *shell, char **av, int *i)
{
	shell->builtin.is_echo_n = FALSE;
	while (av[(*i)])
	{
		if (is_flag_n(av[(*i)]) == TRUE)
		{
			shell->builtin.is_echo_n = TRUE;
			(*i)++;
		}
		else
			break ;
	}
	return (0);
}

static t_bool	is_flag_n(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-')
		i++;
	else
		return (FALSE);
	while (str[i])
	{
		if (str[i] != 'n')
			return (FALSE);
		i++;
	}
	return (TRUE);
}
