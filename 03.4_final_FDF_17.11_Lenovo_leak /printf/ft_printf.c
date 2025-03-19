/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csturny <csturny@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 13:38:59 by csturny           #+#    #+#             */
/*   Updated: 2025/01/21 13:48:39 by csturny          ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "ft_printf.h"

static void	ft_conversion(char c, va_list args, int *len);
char		*ft_strchr( const char *str, int searchedChar);

int	ft_printf(char const *str, ...)
{
	va_list	args;
	int		gl_count;

	if (str == 0)
		return (-1);
	gl_count = 0;
	va_start(args, str);
	while (*str != '\0')
	{
		if (*str == '%')
		{
			str++;
			if (ft_strchr_new("cspdiuxX", *str))
				ft_conversion(*str, args, &gl_count);
			else if (*str == '%')
				ft_char('%', &gl_count);
		}
		else
			ft_char(*str, &gl_count);
		str++;
	}
	va_end(args);
	return (gl_count);
}

static void	ft_conversion(char c, va_list args, int *len)
{
	if (c == 'c')
		ft_char(va_arg(args, int), len);
	else if (c == 's')
		ft_string(va_arg(args, char *), len);
	else if ((c == 'i') || (c == 'd'))
		ft_decimal_b10(va_arg(args, int), len);
	else if (c == 'u')
		ft_unsigned_decimal_b10(va_arg(args, unsigned int), len);
	else if ((c == 'x') || (c == 'X'))
		ft_hexa_b16(va_arg(args, unsigned int), len, c);
	else if (c == 'p')
		ft_uns_pointer(va_arg(args, void *), 0, len);
	else
		ft_char(c, len);
}

char	*ft_strchr_new( const char *str, int searchedChar)
{
	while ((char) searchedChar != *str)
	{
		if (!*str)
			return (NULL);
		str++;
	}
	return ((char *) str);
}

/*
#include <stdio.h>
#include <limits.h>
#include <stdint.h>
#include <string.h>

#include "ft_printf.h"  // Assurez-vous que ft_printf est correctement inclus


int	main(void)
{
	char			c;
	char			*str;
	int				i;
	unsigned int	u;
	char			*ptr;

	c = 'A';
	str = "Gros cul";
	i = -2147483648;
	u = 4294967295;
	ptr = &c;
	
	ft_printf("\nReturn: %d\n", ft_printf("Hello %c! This is %s.", c, str));
	printf("\nReturn: %d\n", printf("Hello %c! This is %s.", c, str)); 
	ft_printf("\nReturn: %d\n", ft_printf("The chosen ones are %d and %u.", i, u));
	printf("\nReturn: %d\n", printf("The chosen ones are %d and %u.", i, u));
	ft_printf("\nReturn: %d\n", ft_printf("Also known as: %x and %X", u, u));
	printf("\nReturn: %d\n", printf("Also known as: %x and %X", u, u));

	ft_printf("\nReturn: %d\n", ft_printf("You live in %p", ptr));
	printf("\nReturn: %d\n", printf("You live in %p", ptr));
	ft_printf("\nReturn: %d\n", ft_printf(0));
	printf("\nReturn: %d\n",  printf(0));
	return (0);
}
*/
