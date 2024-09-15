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

void	ft_lstclear_item(t_next_line **lst)
{
	t_next_line	*temp;

	if (!*lst)
		return ;
	temp = *lst;
	temp->fd = -2;
	if (temp->buffer)
		free (temp->buffer);
	*lst = temp->next;
	if (!temp->next)
		*lst = NULL;
	free (temp);
	temp = NULL;
}

char	*merge(char *word1, char *word2, int f, int i)
{
	char	*res;
	int		j;

	j = 0;
	if (f == -1)
		res = (char *)malloc(sizeof(char) * (ft_strlen(word1) + ft_strlen(word2) + 1));
	else
		res = (char *)malloc(sizeof(char) * (ft_strlen(word1) + f + 2));
	if (!res)
		return (NULL);
	while (word1[i])
	{
		res[i] = word1[i];
		i++;
	}
	while ((f == -1 && word2[j]) || (j < f))
	{
		res[i + j] = word2[j];
		j++;
	}
	res[i + j] = '\0';
	free (word1);
	return (res);
}

static t_next_line	*get_buffer(t_next_line **all_fd, int fd)
{
	t_next_line	*check;
	t_next_line	*new;

	check = *all_fd;
	while (check)
	{
		if (check != NULL && check->fd == fd)
			return (check);
		check = check->next;
	}
	new = (t_next_line *)malloc(sizeof(t_next_line));
	if (!new)
		return (NULL);
	new->fd = fd;
	new->buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!(new->buffer))
	{
		free(new);
		return (NULL);
	}
	new->used_buffer = -1;
	new->buffer[0] = '\0';
	new->next = *all_fd;
	*all_fd = new;
	return (new);
}

static char	*get_result(int fd, t_next_line *current, int i, char *res)
{
	int		bytes_read;

	res = merge(res, current->buffer, i, 0);
	bytes_read = 1;
	current->used_buffer = 1;
	while (i == -1 && bytes_read > 0)
	{
		bytes_read = read(fd, current->buffer, BUFFER_SIZE);
		if (bytes_read == 0)
		{
			current->used_buffer = -1;
			ft_lstclear_item (&current);
			return (res);
		}
		current->buffer[bytes_read] = '\0';
		i = ft_strchr(current->buffer, '\n');
		if (i != -1)
		{
			res = merge(res, current->buffer, i, 0);
			if (ft_strlen(current->buffer + i) == 0)
				current->used_buffer = 0;
			ft_memmove(current->buffer, (current->buffer + i), ft_strlen(current->buffer + i) + 1);
			return (res);
		}
		res = merge(res, current->buffer, i, 0);
		if (ft_strlen(current->buffer) == 0 && bytes_read < BUFFER_SIZE)
			ft_lstclear_item (&current);
	}
	return (res);
}

char	*get_next_line(int fd)
{
	static t_next_line	*all_fd;
	t_next_line			*current;
	int			i;
	char		*res;

	i = -1;
	res = NULL;
	if (fd == -1 || read(fd, res, 0) == -1)
		return (NULL);
	current = get_buffer(&all_fd, fd);
	res = (char *)malloc(sizeof(char));
	res[0] = '\0';
	if (current->used_buffer == 1)
		i = ft_strchr(current->buffer, '\n');
	if (i != -1)
	{
		res = merge(res, current->buffer, i, 0);
		ft_memmove(current->buffer, (current->buffer + i), ft_strlen(current->buffer + i) + 1);
		return (res);
	}
	else
		res = get_result(fd, current, i, res);
	if (ft_strlen(res) == 0)
	{
		free (res);
		return (NULL);
	}
	return (res);
}
