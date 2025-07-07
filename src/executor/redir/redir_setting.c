/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_setting.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlichten <hlichten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 20:30:46 by hlichten          #+#    #+#             */
/*   Updated: 2025/07/07 20:37:45 by hlichten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**set_redir_av(t_shell *shell, char **av);
static char	**copy_args_no_redir(t_shell *shell, char **av, char **new_tab);

void	set_redir_file_type_av(t_shell *shell, char **av)
{
	int	i;

	i = 0;
	advance_to_redir_index(shell, av, &i);
	if (av[i + 1] == NULL)
	{
		ft_putendl_fd("Syntax error: expected file after redirection\n",
			STDERR_FILENO);
		shell->executor.redir_file = NULL;
		shell->executor.redir_type = 0;
		free_tab(&shell->executor.redir_av);
		return ;
	}
	free_ptr((void **)&shell->executor.redir_file);
	shell->executor.redir_file = ft_strndup(av[i + 1], ft_strlen(av[i + 1]));
	if (!shell->executor.redir_file)
		unfructuous_malloc(shell);
	set_redir_type(shell, av[i]);
	free_tab(&shell->executor.redir_av);
	shell->executor.redir_av = set_redir_av(shell, av);
}

void	advance_to_redir_index(t_shell *shell, char **av, int *i)
{
	int	count;

	count = 0;
	*i = 0;
	while (av[*i])
	{
		if (is_redir(av[*i]) == TRUE)
			count++;
		if (count == shell->executor.nb_redir_wip)
			break ;
		(*i)++;
	}
}

static char	**set_redir_av(t_shell *shell, char **av)
{
	char	**new_tab;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (av[i] && !is_redir(av[i]))
	{
		i++;
		j++;
	}
	if (is_redir(av[i]) && av[i + 1])
		i += 2;
	while (av[i] && !is_redir(av[i]))
	{
		i++;
		j++;
	}
	new_tab = malloc(sizeof(char *) * (j + 1));
	if (!new_tab)
		unfructuous_malloc(shell);
	new_tab = copy_args_no_redir(shell, av, new_tab);
	return (new_tab);
}

static char	**copy_args_no_redir(t_shell *shell, char **av, char **new_tab)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (av[i] && !is_redir(av[i]))
	{
		new_tab[i] = ft_strdup(av[i]);
		if (!new_tab[i])
			free_mid_tab(shell, &new_tab, i);
		i++;
	}
	j = i;
	if (is_redir(av[i]) && av[i + 1])
		i += 2;
	while (av[i] && !is_redir(av[i]))
	{
		new_tab[j] = ft_strdup(av[i]);
		if (!new_tab[j])
			free_mid_tab(shell, &new_tab, j);
		i++;
		j++;
	}
	new_tab[j] = NULL;
	return (new_tab);
}
