/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pointer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlaffita <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 19:09:03 by mlaffita          #+#    #+#             */
/*   Updated: 2025/04/02 11:59:19 by mlaffita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/**
 * @brief Convertit une adresse de pointeur en chaîne hexadécimale et l'affiche.
 * 
 * Cette fonction prend une adresse de pointeur, la convertit en une 
 * représentation hexadécimale précédée de "0x", et l'affiche. Elle met 
 * également à jour la longueur totale des caractères imprimés.
 * 
 * @param ptr L'adresse du pointeur à afficher.
 * @param len Pointeur vers la longueur totale des caractères imprimés.
 */

void	ft_pointer(size_t ptr, int *len)
{
	char		str[25];
	int			i;
	const char	*base_char;

	base_char = "0123456789abcdef";
	i = 0;
	write (1, "0x", 2);
	(*len) = (*len) + 2;
	if (ptr == 0)
	{
		ft_putchar_len('0', len);
		return ;
	}
	while (ptr != 0)
	{
		str[i] = base_char[ptr % 16];
		ptr = ptr / 16;
		i++;
	}
	while (i--)
	{
		ft_putchar_len(str[i], len);
	}
}
