/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csturny <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 11:37:42 by csturny           #+#    #+#             */
/*   Updated: 2024/10/04 11:37:42 by csturny          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(const char *src, unsigned int start, size_t len)
{
	char	*sub;
	size_t	i;

	if (!src)
		return (NULL);
	if (start > ft_strlen(src))
		return (ft_strdup(""));
	if (len > ft_strlen(src + start))
		len = ft_strlen(src + start);
	sub = ft_calloc(len + 1, sizeof(char));
	if (!sub)
		return (NULL);
	i = 0;
	while (i < len)
	{
		sub[i] = src[start + i];
		i++;
	}
	return (sub);
}
