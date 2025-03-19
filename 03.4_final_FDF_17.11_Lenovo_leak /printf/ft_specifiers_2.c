/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_specifiers_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csturny <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 15:24:45 by csturny           #+#    #+#             */
/*   Updated: 2024/12/02 15:24:45 by csturny          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_hexa_b16(unsigned int nbr, int *gl_count, char xhex)
{
	char	*hex_base;

	if (xhex == 'X')
		hex_base = "0123456789ABCDEF";
	else if (xhex == 'x')
		hex_base = "0123456789abcdef";
	else
		return ;
	if (nbr < 16)
		ft_char(hex_base[nbr], gl_count);
	else
	{
		ft_hexa_b16(nbr / 16, gl_count, xhex);
		ft_char(hex_base[nbr % 16], gl_count);
	}
}

void	ft_uns_pointer(void *p, int prefix, int *gl_count)
{
	unsigned long	ptr;
	const char		*hex_base;

	hex_base = "0123456789abcdef";
	ptr = (unsigned long)p;
	if (prefix == 0)
		ft_string("0x", gl_count);
	if (ptr >= 16)
	{
		ft_uns_pointer((void *)(ptr / 16), 1, gl_count);
		ft_char(hex_base[ptr % 16], gl_count);
	}
	else
		ft_char(hex_base[ptr], gl_count);
}

/*
dans ft_uns_pointer j ai enleve cette condition!
if (p == NULL) // 
	{
		ft_string("(nil)", gl_count);
		return ;
	}*/
