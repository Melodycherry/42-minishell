/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlaffita <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 18:12:51 by mlaffita          #+#    #+#             */
/*   Updated: 2025/03/09 17:58:24 by mlaffita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(const char *src, int n)
{
	char	*dest;

	dest = (char *) malloc(sizeof(char) * (n + 1));
	if (dest == NULL)
		return (NULL);
	ft_strlcpy(dest, src, n + 1);
	return (dest);
}
