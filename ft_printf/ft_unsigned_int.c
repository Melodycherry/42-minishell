/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unsigned_int.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlaffita <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 19:09:14 by mlaffita          #+#    #+#             */
/*   Updated: 2025/04/02 12:07:00 by mlaffita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/**
 * @brief Affiche un entier non signé et met à jour la longueur totale des caractères imprimés.
 * 
 * Cette fonction gère l'affichage d'un entier non signé en le décomposant 
 * récursivement en chiffres individuels et en les affichant un par un. 
 * Elle met également à jour le compteur de longueur totale des caractères imprimés.
 * 
 * @param u L'entier non signé à afficher.
 * @param len Pointeur vers la longueur totale des caractères imprimés.
 */
void	ft_unsigned_int(unsigned int u, int *len)
{
	if (u >= 10)
		ft_unsigned_int(u / 10, len);
	ft_putchar_len(u % 10 + '0', len);
}
