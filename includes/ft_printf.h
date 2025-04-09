/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlaffita <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 18:57:06 by mlaffita          #+#    #+#             */
/*   Updated: 2024/11/06 15:21:01 by mlaffita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

// library
# include <unistd.h>
# include <stdarg.h>
# include <stddef.h>
# include <stdlib.h>

// fonctions
void	ft_putchar_len(char c, int *len);
void	ft_string(char *str, int *len);
void	ft_number(int nbr, int *len);
void	ft_hexa(unsigned int x, int *len, char hex_case);
void	ft_unsigned_int(unsigned int u, int *len);
void	ft_pointer(size_t ptr, int *len);

int		ft_printf(const char *string, ...);

#endif