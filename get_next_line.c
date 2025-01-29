/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aatieh <aatieh@student.42amman.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 16:43:03 by aatieh            #+#    #+#             */
/*   Updated: 2025/01/29 20:06:03 by aatieh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*merge(char *word1, char *word2, int f, int i)
{
	char	*res;
	int		j;

	j = 0;
	if (f == 0)
		res = malloc(sizeof(char) * (ft_strlen(word1)
					+ ft_strlen(word2) + 1));
	else
		res = malloc(sizeof(char) * (ft_strlen(word1) + f + 2));
	if (!res)
		free(word1);
	while (word1 && word1[i])
	{
		res[i] = word1[i];
		i++;
	}
	while (word1 && ((f == 0 && word2[j]) || (j < f)))
	{
		res[i + j] = word2[j];
		j++;
		res[i + j] = '\0';
	}
	if (word1)
		free(word1);
	return (res);
}

int	first_step(char *buff, int fd, int *bytes_read, char **res)
{
	int		i;

	i = ft_strchr_find(buff, '\n');
	if (ft_strlen(buff))
		*res = merge(*res, buff, i, 0);
	if (!*res)
		return (-1);
	if (i != 0)
	{
		ft_memmove(buff, (buff + i), ft_strlen(buff + i - 1));
		return (i);
	}
	*bytes_read = read(fd, buff, BUFFER_SIZE);
	if (*bytes_read == -1)
	{
		free(*res);
		return (-1);
	}
	ft_bzero((buff + *bytes_read), BUFFER_SIZE - *bytes_read + 1);
	return (i);
}

char	*check_buffer(int fd, char *buff, int bytes_read)
{
	int		i;
	char	*res;

	i = 0;
	res = malloc(sizeof(char));
	if (!res)
		return (NULL);
	res[0] = '\0';
	while (i == 0)
	{
		i = first_step(buff, fd, &bytes_read, &res);
		if (i == -1)
			return (NULL);
		if ((bytes_read < BUFFER_SIZE && !ft_strlen(buff) && !i))
		{
			if (!ft_strlen(res))
			{
				free(res);
				return (NULL);
			}
			return (res);
		}
	}
	return (res);
}

char	*assgine_buff(char *buff)
{
	if (buff)
		return (buff);
	buff = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buff)
		return (NULL);
	ft_bzero(buff, BUFFER_SIZE + 1);
	return (buff);
}

char	*get_next_line(int fd)
{
	static char	*buff;
	char		*res;

	if (fd == -1 || BUFFER_SIZE <= 0)
		return (NULL);
	buff = assgine_buff(buff);
	if (!buff)
		return (NULL);
	res = check_buffer(fd, buff, BUFFER_SIZE);
	if (res == NULL || !ft_strncmp(buff, "", 2))
	{
		free(buff);
		buff = NULL;
	}
	return (res);
}
