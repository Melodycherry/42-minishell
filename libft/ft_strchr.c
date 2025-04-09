/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlaffita <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 16:07:37 by mlaffita          #+#    #+#             */
/*   Updated: 2024/10/27 15:58:47 by mlaffita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	unsigned char	d;

	d = (unsigned char)c;
	while (*s != '\0')
	{
		if (*s == d)
			return ((char *) s);
		s++;
	}
	if (d == '\0')
		return ((char *) s);
	return (NULL);
}
/*
#include <stdio.h>
#include <string.h>

int main()
{
	char	str[] = "Hello world";

	char *result = ft_strchr(str, 'l');
	printf(" caractere trouve a la position %ld\n", result - str);
	//
	char *resultat = strchr(str, 'l');
	printf(" caractere trouve a la position %ld\n", resultat - str);
	return (0);
}
*/