/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlaffita <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 16:42:12 by mlaffita          #+#    #+#             */
/*   Updated: 2024/10/27 16:07:14 by mlaffita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	const char	*last = 0;

	c = (unsigned char)c;
	while (*s != '\0')
	{
		if (*s == (char)c)
			last = s;
		s++;
	}
	if (c == '\0')
		return ((char *) s);
	return ((char *) last);
}
/*
#include <stdio.h>
#include <string.h>

int main()
{
	const char s[] = "hello world";
	char *result = ft_strrchr(s, 'l');
	printf("caractere trouve a la position %ld\n", result - s);
	//
	char *resultat = strrchr(s, 'l');
	printf("caractere trouve a la position %ld\n", resultat - s);
	return (0);
}
*/