/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hexa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlaffita <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 19:08:54 by mlaffita          #+#    #+#             */
/*   Updated: 2025/04/02 12:03:46 by mlaffita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/**
 * @brief Convertit un entier non signé en une représentation hexadécimale et l'affiche.
 * 
 * Cette fonction prend un entier non signé, le convertit en une chaîne hexadécimale 
 * (en majuscules ou minuscules selon le paramètre `hex_case`), et l'affiche. 
 * Elle met également à jour la longueur totale des caractères imprimés.
 * 
 * @param x L'entier non signé à convertir et afficher.
 * @param len Pointeur vers la longueur totale des caractères imprimés.
 * @param hex_case Détermine si la représentation hexadécimale est en majuscules ('X') 
 * ou en minuscules ('x').
 */
void	ft_hexa(unsigned int x, int *len, char hex_case)
{
	char	str[25];
	char	*base_char;
	int		i;

	if (hex_case == 'X')
		base_char = "0123456789ABCDEF";
	else
		base_char = "0123456789abcdef";
	i = 0;
	if (x == 0)
	{
		ft_putchar_len('0', len);
		return ;
	}
	while (x != 0)
	{
		str[i] = base_char[x % 16];
		x = x / 16;
		i++;
	}
	while (i--)
		ft_putchar_len(str[i], len);
}
