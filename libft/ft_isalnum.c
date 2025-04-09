/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlaffita <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 17:10:38 by mlaffita          #+#    #+#             */
/*   Updated: 2024/10/23 14:42:39 by mlaffita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalnum(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')
		|| (c >= '0' && c <= '9'))
		return (1);
	return (0);
}
/*
#include <stdio.h>

int	main()
{
	char	test1 = 'a';
	char	test2 = 'B';
	char	test3 = '7';
	char	test4 = ' ';

	printf("test 1 %c, : %d\n", test1, ft_isalnum(test1));
	printf("test 2 %c, : %d\n", test2, ft_isalnum(test2));
	printf("test 3 %c, : %d\n", test3, ft_isalnum(test3));
	printf("test 4 %c, : %d\n", test4, ft_isalnum(test4));
	return (0);
}
*/