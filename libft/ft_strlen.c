/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlichten <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 15:21:12 by mlaffita          #+#    #+#             */
/*   Updated: 2025/05/14 18:11:40 by hlichten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strlen(const char *str)
{
	int	len;

	len = 0;
	while (str[len])
	{
		len++;
	}
	return (len);
}
/*
#include <stdio.h>

int main()
{
    char testchaine[] = "coucou";
    
    ft_strlen(testchaine);
    printf("%d", ft_strlen(testchaine));
    return  (0);
}
*/
