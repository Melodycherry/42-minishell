/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlichten <hlichten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 20:36:14 by hlichten          #+#    #+#             */
/*   Updated: 2025/07/07 20:36:16 by hlichten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*join_free(t_shell *shell, char *s1, char *s2, int len_s2)
{
	size_t	len_s1;
	char	*str;

	(void)shell;
	len_s1 = 0;
	if (!s2 || len_s2 < 0)
		return (free_ptr((void **)&s1));
	if (s1)
		len_s1 = ft_strlen(s1);
	str = malloc(len_s1 + len_s2 + 1);
	if (!str)
	{
		free_ptr((void **)&s1);
		unfructuous_malloc(shell);
	}
	if (s1)
		ft_memcpy(str, s1, len_s1);
	ft_memcpy(str + len_s1, s2, len_s2);
	str[len_s1 + len_s2] = '\0';
	free_ptr((void **)&s1);
	return (str);
}

int	get_segment_len(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '$' && str[i] != '"')
		i++;
	return (i);
}
