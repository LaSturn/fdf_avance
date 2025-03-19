/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csturny <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 14:54:50 by csturny           #+#    #+#             */
/*   Updated: 2024/10/03 14:54:50 by csturny          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t	i;

	if (!s && !c && !n)
		return (NULL);
	i = 0;
	while (i < n)
	{
		if (*(const unsigned char *)(s + i) == (unsigned char) c)
			return ((void *)((const unsigned char *) s + i));
		i++;
	}
	return (NULL);
}
