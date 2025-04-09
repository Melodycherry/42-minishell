/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlaffita <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 16:53:07 by mlaffita          #+#    #+#             */
/*   Updated: 2024/10/27 13:36:32 by mlaffita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char		*d;
	const unsigned char	*s;

	d = (unsigned char *)dst;
	s = (const unsigned char *)src;
	if (!dst && !src)
		return (NULL);
	if (len == 0 || dst == src)
		return (dst);
	if (src < dst)
		while (len--)
			d[len] = s[len];
	else
		while (len--)
			*d++ = *s++;
	return (dst);
}
/*
#include <stdio.h>
int main()
{
	char	source[] = "hello world!";
	char	destination[20];
	size_t	n;

	n = 14;
	ft_memmove(destination, source, n);
	printf("source %s\n", source);
	printf("destination %s\n", destination);
	//
	memmove(destination, source, n);
	printf("source %s\n", source);
	printf("destination %s\n", destination);
	return (0);
}
*/