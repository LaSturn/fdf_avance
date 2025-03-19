/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csturny <csturny@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 10:01:02 by csturny           #+#    #+#             */
/*   Updated: 2025/01/22 10:01:25 by csturny          ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "libft.h"

#include <stdlib.h>

int	ft_atoi_base(const char *str, int str_base)
{
	int	res = 0;
	int	sign = 1;
	int	i = 0;
	int c;
	if (*str == '-')
	{
		sign = -1;
		str++;
	}
	while (str[i])
	{
		if (str[i] >= '0' && str[i] <= '9')
			c = str[i] - '0';
		else if (str[i] >= 'a' && str[i] <= 'f')
			c = str[i] - 'a' + 10;
		else if (str[i] >= 'A' && str[i] <= 'F')
			c = str[i] - 'A' + 10;
		else
			break;
		res = res * str_base + c;
		i++;
	}
	return (res * sign);
}