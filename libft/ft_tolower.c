/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlaffita <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 15:35:56 by mlaffita          #+#    #+#             */
/*   Updated: 2024/10/23 14:45:10 by mlaffita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_tolower(int c)
{
	if (c >= 'A' && c <= 'Z')
		return (c = c + 32);
	return (c);
}
/*
#include <stdio.h>

int	main()
{
	char test1 = 'A';
	char test2 = 'B';
	char test3 = 'c';

	printf("test 1 : %c = %c\n", test1, ft_tolower(test1));
	printf("test 2 : %c = %c\n", test2, ft_tolower(test2));
	printf("test 3 : %c = %c\n", test3, ft_tolower(test3));
	return (0);
}
*/