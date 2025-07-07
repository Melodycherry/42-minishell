/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlichten <hlichten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 20:36:27 by hlichten          #+#    #+#             */
/*   Updated: 2025/07/07 20:36:29 by hlichten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_bool	is_valid_var_name(t_token *token, t_shell *shell)
{
	int		i;
	char	*line;

	(void)shell;
	i = 0;
	line = token->value;
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

t_bool	var_exist(char **envp, const char *var_env, int len)
{
	int		i;
	int		var_len;
	char	*equal_sign;

	i = 0;
	while (envp[i])
	{
		equal_sign = ft_strchr(envp[i], '=');
		if (equal_sign)
		{
			var_len = (int)(equal_sign - envp[i]);
			if (var_len == len && ft_strncmp(envp[i], var_env, len) == 0)
				return (TRUE);
		}
		else
			if (ft_strncmp(envp[i], (char *)var_env, len) == 0)
				return (TRUE);
		i++;
	}
	return (FALSE);
}

int	pos_var_env(char **envp, char *var_env, int len)
{
	int		i;
	char	*equal_sign;

	i = 0;
	while (envp[i])
	{
		equal_sign = ft_strchr(envp[i], '=');
		if (equal_sign)
		{
			if (ft_strncmp(envp[i], var_env, (int)(equal_sign - envp[i])) == 0
				&& (envp[i][len] == '='))
				return (i);
		}
		else
			if (ft_strncmp(envp[i], (char *)var_env, len) == 0)
				return (i);
		i++;
	}
	return (i);
}

char	*recup_var(char **envp, char *var_env, int len)
{
	int		i;
	int		j;
	int		k;
	char	*equal_sign;

	i = 0;
	while (envp[i])
	{
		equal_sign = ft_strchr(envp[i], '=');
		j = (int)(equal_sign - envp[i]);
		if (ft_strncmp(envp[i], var_env, j) == 0 && (envp[i][len] == '='))
		{
			j++;
			k = j;
			while (envp[i][j])
				j++;
			return (&envp[i][k]);
		}
		i++;
	}
	return (NULL);
}
