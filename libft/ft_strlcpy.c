/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlaffita <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 15:45:51 by mlaffita          #+#    #+#             */
/*   Updated: 2024/10/23 16:36:15 by mlaffita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

unsigned int	ft_strlcpy(char *dest, const char *src, unsigned int size)
{
	unsigned int	s;
	unsigned int	i;

	s = 0;
	i = 0;
	while (src[s] != '\0')
		s++;
	if (size == 0)
		return (s);
	while (src[i] != '\0' && i < size - 1)
	{
		dest[i] = src[i];
		i++;
	}
	if (size > 0)
		dest[i] = '\0';
	return (s);
}
/*
#include <stdio.h>
int	main()
{
	char	source[] = "Hello world";
	char	destination[20];
	unsigned int	size;
	unsigned int	length;

	size = 20;
	length = ft_strlcpy(destination, source, size);
	printf("source : %s\n", source);
	printf("destinaton : %s\n", destination);
	printf("longueur source : %u\n", length);
	return(0);
}
*/