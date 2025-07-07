/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlichten <hlichten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 20:32:23 by hlichten          #+#    #+#             */
/*   Updated: 2025/07/07 20:40:09 by hlichten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	filtr_out_var(t_shell *shell, char **new_tab,
				char *name, t_bool is_export);
static void	remove_var(t_shell *shell, char **old_tab,
				char *name, t_bool is_export);
static void	copy_or_exit(t_shell *shell, char **new_tab, char *src, int *j);

int	builtin_unset(t_shell *shell, char **av)
{
	int	i;

	i = 1;
	if (av[1][0] == '-')
	{
		ft_putendl_fd("Invalid option", STDERR_FILENO);
		return (2);
	}
	while (av[i])
	{
		remove_var(shell, shell->cmd.envp_exp, av[i], TRUE);
		remove_var(shell, shell->cmd.envp_copy, av[i], FALSE);
		i++;
	}
	return (0);
}

static void	remove_var(t_shell *shell,
			char **old_tab, char *name, t_bool is_export)
{
	int		i;
	int		tab_len;
	char	**new_tab;

	if (!old_tab)
		return ;
	i = 0;
	while (old_tab[i])
	{
		if ((ft_strncmp(old_tab[i], name, ft_strlen(name)) == 0)
			&& (old_tab[i][ft_strlen(name)] == '='
			|| old_tab[i][ft_strlen(name)] == '\0'))
			break ;
		i++;
	}
	if (!old_tab[i])
		return ;
	tab_len = 0;
	while (old_tab[tab_len])
		tab_len++;
	new_tab = malloc_tab(shell, tab_len - 1);
	if (!new_tab)
		unfructuous_malloc(shell);
	filtr_out_var(shell, new_tab, name, is_export);
	replace_tab(shell, new_tab, is_export);
}

static void	filtr_out_var(t_shell *shell, char **new_tab, char *name,
			t_bool is_export)
{
	int		i;
	int		j;
	int		len;
	char	**old_tab;

	i = 0;
	j = 0;
	len = ft_strlen(name);
	if (is_export == TRUE)
		old_tab = shell->cmd.envp_exp;
	else
		old_tab = shell->cmd.envp_copy;
	while (old_tab[i])
	{
		if (!(ft_strncmp(old_tab[i], name, len) == 0
				&& (old_tab[i][len] == '=' || old_tab[i][len] == '\0')))
			copy_or_exit(shell, new_tab, old_tab[i], &j);
		i++;
	}
	new_tab[j] = NULL;
}

static void	copy_or_exit(t_shell *shell, char **new_tab, char *src, int *j)
{
	new_tab[*j] = ft_strdup(src);
	if (!new_tab[*j])
	{
		free_mid_tab(shell, &new_tab, *j);
		unfructuous_malloc(shell);
	}
	(*j)++;
}

void	replace_tab(t_shell *shell, char **new_tab, t_bool is_export)
{
	if (is_export == TRUE)
	{
		if (shell->cmd.envp_exp != new_tab)
			free_tab(&shell->cmd.envp_exp);
		shell->cmd.envp_exp = new_tab;
	}
	else
	{
		if (shell->cmd.envp_copy != new_tab)
			free_tab(&shell->cmd.envp_copy);
		shell->cmd.envp_copy = new_tab;
	}
}
