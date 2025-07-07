/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlichten <hlichten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 20:33:06 by hlichten          #+#    #+#             */
/*   Updated: 2025/07/07 20:33:08 by hlichten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_env(char *value, int to_tab, t_shell *shell)
{
	if (to_tab == TO_EXPORT)
		insert_env_export(shell, value, shell->cmd.envp_exp, TRUE);
	else if (to_tab == TO_ENV)
		insert_env_export(shell, value, shell->cmd.envp_copy, TRUE);
	else if (to_tab == TO_BOTH)
	{
		insert_env_export(shell, value, shell->cmd.envp_exp, TRUE);
		insert_env_export(shell, value, shell->cmd.envp_copy, FALSE);
	}
}

t_bool	is_valid_name(char *line)
{
	int	i;

	i = 0;
	while (line[i] && line[i] != '=')
	{
		if (line[0] == '_' || ft_isalpha(line[0]))
			i++;
		else
			return (FALSE);
		if (line[i] == '_' || ft_isalnum(line[i]))
			i++;
	}
	return (TRUE);
}

char	**malloc_tab(t_shell *shell, int tab_len)
{
	char	**new_tab;

	(void)shell;
	new_tab = malloc(sizeof(char *) * (tab_len + 1));
	if (!new_tab)
		unfructuous_malloc(shell);
	return (new_tab);
}

void	insert_env_export(t_shell *shell, char *value,
				char **tab, t_bool is_export)
{
	int		index;
	int		var_len;
	char	*equal_sign;

	index = 0;
	equal_sign = ft_strchr(value, '=');
	if (equal_sign)
		var_len = (int)(equal_sign - value);
	else
		var_len = ft_strlen(value);
	if (var_exist(tab, value, var_len) == TRUE)
	{
		index = pos_var_env(tab, value, var_len);
		free_ptr((void **)&tab[index]);
		tab[index] = ft_strndup(value, ft_strlen(value));
		if (!tab[index])
			unfructuous_malloc(shell);
		return ;
	}
	if (var_exist(tab, value, var_len) == FALSE)
		put_in_env_export(shell, tab, value, is_export);
}
