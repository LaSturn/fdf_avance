/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csturny <csturny@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 11:25:58 by csturny           #+#    #+#             */
/*   Updated: 2025/01/20 13:16:39 by csturny          ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "libft.h"
#include "get_next_line.h"

static char		*read_and_store(int fd, char *data);
static char		*buf_to_data(char *data, char *buf);
static char		*extract_completed_line(char **data);

char	*get_next_line(int fd)
{
	static char	*data = NULL;
	char		*completed_line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
	{
		if (data)
			free(data);
		data = NULL;
		return (NULL);
	}
	data = read_and_store(fd, data);
	if (!data)
		return (NULL);
	completed_line = extract_completed_line(&data);
	if (!completed_line)
	{
		free(data);
		data = NULL;
	}
	return (completed_line);
}

static char	*read_and_store(int fd, char *data)
{
	ssize_t	count_read;
	char	buffer[BUFFER_SIZE + 1];

	count_read = read(fd, buffer, BUFFER_SIZE);
	while (count_read > 0)
	{
		buffer[count_read] = '\0';
		data = buf_to_data(data, buffer);
		if (!data)
			return (NULL);
		if (ft_strchr(buffer, '\n'))
			break ;
		count_read = read(fd, buffer, BUFFER_SIZE);
	}
	if (count_read == -1)
	{
		free(data);
		return (NULL);
	}
	return (data);
}

static char	*buf_to_data(char *data, char *buf)
{
	char	*tmp;

	if (!data)
		data = ft_strdup(buf);
	else
	{
		tmp = data;
		data = ft_strjoin(tmp, buf);
		free(tmp);
	}
	return (data);
}

static char	*extract_completed_line(char **data)
{
	char	*c_line;
	char	*remaining;
	size_t	i;

	i = 0;
	if (!*data || **data == '\0')
		return (NULL);
	while ((*data)[i] != '\n' && (*data)[i] != '\0')
		i++;
	if ((*data)[i] == '\n')
	{
		c_line = ft_substr(*data, 0, i + 1);
		remaining = ft_strdup(*data + i + 1);
	}
	else
	{
		c_line = ft_strdup(*data);
		remaining = NULL;
	}
	free(*data);
	*data = remaining;
	return (c_line);
}


