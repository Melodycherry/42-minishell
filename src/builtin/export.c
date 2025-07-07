/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlichten <hlichten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 20:33:01 by hlichten          #+#    #+#             */
/*   Updated: 2025/07/07 20:33:03 by hlichten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_export(t_shell *shell, char **av)
{
	int	len;
	int	i;

	if (av[1] && av[1][0] == '-')
	{
		ft_putendl_fd("Invalid option", STDERR_FILENO);
		return (2);
	}
	len = ft_tablen(av);
	i = 1;
	if (len == 1)
		print_export(shell->cmd.envp_exp);
	else
	{
		while (av[i])
		{
			checking_var(shell, av[i]);
			i++;
		}
	}
	return (0);
}

t_bool	checking_var(t_shell *shell, char *line)
{
	int	i;

	i = 0;
	if (is_valid_name(line) == FALSE)
		return (printf("Var name not valid\n"),
			error_syntax_export(line), FALSE);
	while (line[i])
	{
		while (line[i] == '_' || ft_isalnum(line[i]))
			i++;
		if (line[i] == '=')
			return (set_env(line, TO_BOTH, shell), TRUE);
		else
			return (set_env(line, TO_EXPORT, shell), TRUE);
	}
	return (TRUE);
}

void	put_in_env_export(t_shell *shell, char **old_tab,
		char *new_value, t_bool is_export)
{
	int		i;
	char	**new_tab;

	i = 0;
	new_tab = malloc_tab(shell, ft_tablen(old_tab) + 1);
	if (!new_tab)
		unfructuous_malloc(shell);
	while (i < ft_tablen(old_tab))
	{
		new_tab[i] = ft_strdup(old_tab[i]);
		if (new_tab[i] == NULL)
			free_mid_tab(shell, &new_tab, i);
		i++;
	}
	new_tab[i] = ft_strdup(new_value);
	if (new_tab[i] == NULL)
		free_mid_tab(shell, &new_tab, i);
	i++;
	new_tab[i] = 0;
	replace_tab(shell, new_tab, is_export);
}

void	print_export(char **tab)
{
	int		i;
	char	*line;
	char	*equal_sign;

	i = 0;
	bubble_tab(tab);
	while (tab[i])
	{
		line = tab[i];
		equal_sign = ft_strchr(line, '=');
		if (equal_sign)
			printf("declare -x %.*s=\"%s\"\n", (int)(equal_sign - line),
				line, equal_sign + 1);
		else
			printf("declare -x %s\n", line);
		i++;
	}
}
