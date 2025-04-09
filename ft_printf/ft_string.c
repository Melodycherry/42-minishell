/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_string.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlaffita <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 19:09:10 by mlaffita          #+#    #+#             */
/*   Updated: 2025/04/02 12:06:05 by mlaffita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/**
 * @brief Affiche une chaîne de caractères et met à jour la longueur totale des caractères imprimés.
 * 
 * Cette fonction affiche une chaîne de caractères sur la sortie standard. 
 * Si la chaîne est nulle (`NULL`), elle affiche "(null)" à la place. 
 * Elle met également à jour le compteur de longueur totale des caractères imprimés.
 * 
 * @param str La chaîne de caractères à afficher.
 * @param len Pointeur vers la longueur totale des caractères imprimés.
 */
void	ft_string(char *str, int *len)
{
	size_t	i;

	i = 0;
	if (!str)
	{
		write (1, "(null)", 6);
		(*len) = (*len) + 6;
		return ;
	}
	while (str[i] != '\0')
	{
		ft_putchar_len(str[i], len);
		i++;
	}
}
