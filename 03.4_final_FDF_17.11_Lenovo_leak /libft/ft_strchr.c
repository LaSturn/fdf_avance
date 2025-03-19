/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csturny <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 14:21:13 by csturny           #+#    #+#             */
/*   Updated: 2024/10/03 14:21:13 by csturny          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr( const char *str, int searchedChar)
{
	while ((char) searchedChar != *str)
	{
		if (!*str)
			return (NULL);
		str++;
	}
	return ((char *) str);
}
