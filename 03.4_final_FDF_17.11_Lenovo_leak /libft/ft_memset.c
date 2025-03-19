/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csturny <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 20:59:18 by csturny           #+#    #+#             */
/*   Updated: 2024/10/09 15:09:03 by csturny          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *ptr, int value, size_t count)
{
	unsigned char	*a;

	a = (unsigned char *)ptr;
	while (count > 0)
	{
		*a++ = (unsigned char)value;
		count--;
	}
	return (ptr);
}
