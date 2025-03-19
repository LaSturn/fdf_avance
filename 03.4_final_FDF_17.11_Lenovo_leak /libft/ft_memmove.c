/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csturny <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 16:09:14 by csturny           #+#    #+#             */
/*   Updated: 2024/10/03 16:09:14 by csturny          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char	*s;
	char	*d;

	s = (char *)src;
	d = (char *)dst;
	if (s <= d)
	{
		s += len - 1;
		d += len - 1;
		while (len-- && (src != NULL || dst != NULL))
			*d-- = *s--;
	}
	else
	{
		while (len-- && (src != NULL || dst != NULL))
			*d++ = *s++;
	}
	return (dst);
}
