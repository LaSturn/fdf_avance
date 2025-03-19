/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csturny <csturny@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 09:06:51 by csturny           #+#    #+#             */
/*   Updated: 2025/01/21 13:45:47 by csturny          ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>
# include <stdint.h> // Nécessaire pour uintptr_t

/* ft_printf.c y.c static ft_converstion */
int		ft_printf(char const *str, ...);
char	*ft_strchr_new(const char *s, int c);
/* ft_printf_specifiers.c et 2*/
void	ft_char(char c, int *gl_count);
void	ft_string(char *s, int *gl_count);
void	ft_decimal_b10(int nbr, int *gl_count);
void	ft_unsigned_decimal_b10(unsigned int nbr, int *gl_count);
void	ft_hexa_b16(unsigned int nbr, int *gl_count, char xhex);
void	ft_uns_pointer(void *p, int prefix, int *gl_count);

#endif