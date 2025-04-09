/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_len.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlaffita <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 19:09:06 by mlaffita          #+#    #+#             */
/*   Updated: 2025/04/02 12:04:50 by mlaffita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/**
 * @brief Affiche un caractère et met à jour la longueur totale des caractères imprimés.
 * 
 * Cette fonction écrit un caractère sur la sortie standard et incrémente 
 * le compteur de longueur totale des caractères imprimés.
 * 
 * @param c Le caractère à afficher.
 * @param len Pointeur vers la longueur totale des caractères imprimés.
 */
void	ft_putchar_len(char c, int *len)
{
	write(1, &c, 1);
	(*len)++;
}
