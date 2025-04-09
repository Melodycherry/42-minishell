/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_number.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlaffita <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 19:08:58 by mlaffita          #+#    #+#             */
/*   Updated: 2025/04/02 12:02:16 by mlaffita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/**
 * @brief Affiche un entier et met à jour la longueur totale des caractères imprimés.
 * 
 * Cette fonction gère l'affichage d'un entier, y compris les cas particuliers 
 * comme le plus petit entier signé (-2147483648). Elle utilise la récursivité 
 * pour décomposer l'entier en chiffres individuels et les afficher un par un.
 * 
 * En plus d'afficher un entier, elle met à jour un compteur (len) qui suit 
 * la longueur totale des caractères imprimés. 
 * 
 * @param nbr L'entier à afficher.
 * @param len Pointeur vers la longueur totale des caractères imprimés.
 */
void	ft_number(int nbr, int *len)
{
	if (nbr == -2147483648)
	{
		write(1, "-2147483648", 11);
		(*len) = (*len) + 11;
		return ;
	}
	if (nbr > 9)
	{
		ft_number(nbr / 10, len);
		ft_number(nbr % 10, len);
	}
	else if (nbr >= 0 && nbr <= 9)
	{
		ft_putchar_len(nbr + '0', len);
	}
	else if (nbr < 0)
	{
		ft_putchar_len('-', len);
		ft_number(nbr * -1, len);
	}
}
