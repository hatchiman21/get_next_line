/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aatieh <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 16:30:44 by aatieh            #+#    #+#             */
/*   Updated: 2024/09/14 16:30:47 by aatieh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <string.h>

char	*merge(char *res, char *word)
{
	char	*temp;

	temp = res;
	res = ft_strjoin(temp, word);
	free (word);
	free (temp);
	return (res);
}

int	ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (( s[i]))
	{
		if (s[i] == (char)c)
			return (i + 1);
		i++;
	}
	return (-1);
}




static char	*get_result(int fd, char *buff, int i, char *res, int *used_buffer)
{	
	int		bytes_read;

	bytes_read = 1;
	*used_buffer = 1;
	while (i == -1 && bytes_read > 0)
	{
		bytes_read = read(fd, buff, BUFFER_SIZE);
		if (bytes_read == 0)
		{
			*used_buffer = -1;
			free (buff);
			buff = NULL;
			return (res);
		}
		buff[bytes_read] = '\0';
		i = ft_strchr(buff, '\n');
		if (i != -1)
		{
			res = merge(res, ft_substr(buff, 0, i));
			if (!(buff + i + 1))
				*used_buffer = 0;
			ft_memmove(buff, (buff + i), ft_strlen(buff + i) + 1);
			return (res);
		}
		res = merge(res, ft_substr(buff, 0, ft_strlen(buff)));
		if (ft_strlen(buff) == 0 && bytes_read < BUFFER_SIZE)
		{
			free (buff);
			buff = NULL;
		}
	}
	return (res);
}

void	assgine_res(char **res)
{
	*res = (char *)malloc(sizeof(char));
	*res[0] = '\0';
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	static	int	used_buffer;
	int			i;
	char		*res;

	i = -1;
	if (!used_buffer)
		used_buffer = -1;
	if (fd == -1)
		return (NULL);
	if (used_buffer == -1)
	{
		used_buffer = 0;
		buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
		buffer[0] = '\0';
	}
	if (read(fd, buffer, 0) == -1)
	{
		used_buffer = -1;
		free (buffer);
		buffer = NULL;
		return (NULL);
	}
	assgine_res(&res);
	if (used_buffer == 1)
		i = ft_strchr(buffer, '\n');
	if (i != -1)
	{
		res = merge(res, ft_substr(buffer, 0, i));
		ft_memmove(buffer, (buffer + i), ft_strlen(buffer + i) + 1);
		return (res);
	}
	else
	res = get_result(fd, buffer, i, res, &used_buffer);
	if (ft_strlen(res) == 0)
	{
		free (res);
		return (NULL);
	}
	return (res);
}
