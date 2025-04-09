/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlaffita <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 15:15:10 by mlaffita          #+#    #+#             */
/*   Updated: 2024/10/23 14:45:05 by mlaffita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_toupper(int c)
{
	if (c >= 'a' && c <= 'z')
		return (c = c - 32);
	return (c);
}
/*
#include <stdio.h>

int	main()
{
	char test1 = 'a';
	char test2 = 'b';
	char test3 = 'C';

	printf("test 1 : %c = %c\n", test1, ft_toupper(test1));
	printf("test 2 : %c = %c\n", test2, ft_toupper(test2));
	printf("test 3 : %c = %c\n", test3, ft_toupper(test3));
	return (0);
}
*/