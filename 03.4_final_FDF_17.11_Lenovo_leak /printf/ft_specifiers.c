/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_specifiers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csturny <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 14:15:39 by csturny           #+#    #+#             */
/*   Updated: 2024/12/02 14:15:39 by csturny          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_char(char c, int *gl_count)
{
	write(1, &c, 1);
	(*gl_count)++;
}

void	ft_string(char *s, int *gl_count)
{
	if (!s)
		ft_string("(null)", gl_count);
	else
	{
		while (*s)
		{
			ft_char(*s, gl_count);
			s++;
		}
	}
}

void	ft_decimal_b10(int nbr, int *gl_count)
{
	long	nb;

	nb = nbr;
	if (nb == -2147483648)
	{
		ft_string("-2147483648", gl_count);
		return ;
	}
	if (nb < 0)
	{
		ft_char('-', gl_count);
		nb *= (-1);
	}
	if (nb > 9)
	{
		ft_decimal_b10(nb / 10, gl_count);
		ft_decimal_b10(nb % 10, gl_count);
	}
	else
		ft_char(nb + '0', gl_count);
}

void	ft_unsigned_decimal_b10(unsigned int nbr, int *gl_count)
{
	if (nbr > 9)
	{
		ft_unsigned_decimal_b10(nbr / 10, gl_count);
		ft_unsigned_decimal_b10(nbr % 10, gl_count);
	}
	else
		ft_char(nbr + '0', gl_count);
}
