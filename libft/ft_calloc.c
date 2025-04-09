/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlaffita <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 15:20:52 by mlaffita          #+#    #+#             */
/*   Updated: 2024/10/27 15:33:34 by mlaffita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	size_t	i;
	char	*str;

	i = count * size;
	str = (char *)malloc(sizeof(char) * i);
	if (str == NULL)
		return (NULL);
	ft_bzero(str, i);
	return (str);
}
/*
#include <stdio.h>

int main()
{
	int	*tab;
	int n = 10;
	int i = 0;

	tab = (int *) ft_calloc(n, sizeof(int));
	if (tab == NULL)
	{
		printf("Echec allocation memoire");
		return (1);
	}
	while (i < n)
	{
		printf("tab[%d] = %d\n", i, tab[i]);
		i++;
	}
	free(tab);
	return (0);
}
*/