/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlaffita <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 22:34:06 by mlaffita          #+#    #+#             */
/*   Updated: 2025/04/02 11:56:04 by mlaffita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/**
 * @brief Vérifie le caractère de format et appelle la fonction correspondante.
 * 
 * Cette fonction analyse le caractère suivant un '%' dans la chaîne de format
 * et appelle la fonction appropriée pour traiter le type de donnée correspondant.
 * 
 * @param s Caractère de format (par exemple, 's', 'd', 'x', etc.).
 * @param args Liste des arguments variadiques.
 * @param len Pointeur vers la longueur totale des caractères imprimés.
 * @param i Pointeur vers l'index actuel dans la chaîne de format.
 */
static void	ft_printf_check(char s, va_list *args, int *len, int *i)
{
	if (s == 's')
		ft_string(va_arg(*args, char *), len);
	else if (s == 'd' || s == 'i')
		ft_number(va_arg(*args, int), len);
	else if (s == 'u')
		ft_unsigned_int(va_arg(*args, unsigned int), len);
	else if (s == 'x')
		ft_hexa(va_arg(*args, unsigned int), len, 'x');
	else if (s == 'X')
		ft_hexa(va_arg(*args, unsigned int), len, 'X');
	else if (s == 'p')
		ft_pointer(va_arg(*args, size_t), len);
	else if (s == 'c')
		ft_putchar_len(va_arg(*args, int), len);
	else if (s == '%')
		ft_putchar_len('%', len);
	else
		(*i)--;
}

/**
 * @brief Implémentation personnalisée de la fonction printf.
 * 
 * Cette fonction reproduit le comportement de la fonction standard `printf`.
 * Elle prend une chaîne de format et des arguments variadiques, puis imprime
 * les données formatées en fonction des spécificateurs de format.
 * 
 * @param string Chaîne de format contenant le texte et les spécificateurs.
 * @param ... Liste des arguments variadiques correspondant aux spécificateurs.
 * @return int La longueur totale des caractères imprimés.
 */
int	ft_printf(const char *string, ...)
{
	va_list	args;
	int		i;
	int		len;

	i = 0;
	len = 0;
	va_start(args, string);
	while (string[i] != '\0')
	{
		if (string[i] == '%')
		{
			i++;
			ft_printf_check(string[i], &args, &len, &i);
			i++;
		}
		else
		{
			ft_putchar_len((char)string[i], &len);
			i++;
		}
	}
	va_end(args);
	return (len);
}
