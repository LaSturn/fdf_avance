/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csturny <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 14:53:12 by csturny           #+#    #+#             */
/*   Updated: 2024/10/05 14:53:12 by csturny          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_word_len(char const *str, char c)
{
	int	len;

	len = 0;
	while (*str && *str != c)
	{
		len++;
		str++;
	}
	return (len);
}

static int	ft_count_words(char const *str, char c)
{
	int	nb_w;

	nb_w = 0;
	while (*str)
	{
		if (*str != c)
		{
			nb_w++;
			str += ft_word_len(str, c);
		}
		else
			str++;
	}
	return (nb_w);
}

static void	*ft_free_split(char **s_split)
{
	int	i;

	i = 0;
	while (s_split[i])
		free(s_split[i++]);
	free(s_split);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	char	**s_split;
	int		i;
	int		nb_w;

	if (!s)
		return (NULL);
	nb_w = ft_count_words(s, c);
	s_split = malloc(sizeof(char *) * (nb_w + 1));
	if (!s_split)
		return (NULL);
	s_split[nb_w] = NULL;
	i = 0;
	while (*s)
	{
		if (*s != c)
		{
			s_split[i] = ft_substr(s, 0, ft_word_len(s, c));
			if (!s_split[i++])
				return (ft_free_split(s_split));
			s += ft_word_len(s, c);
		}
		else
			s++;
	}
	return (s_split);
}
