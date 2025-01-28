/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aatieh <aatieh@student.42amman.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 16:43:10 by aatieh            #+#    #+#             */
/*   Updated: 2025/01/28 19:23:28 by aatieh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

int	ft_strchr(const char *s, int c)
{
	int	i;

	i = 1;
	while (s[i - 1])
	{
		if (s[i - 1] == (char)c)
			return (i);
		i++;
	}
	return (0);
}

void	ft_bzero(void *s, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
		((unsigned char *)s)[i++] = '\0';
}

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t	i;

	i = 0;
	if (!src && !dest)
		return (0);
	if ((size_t)dest - (size_t)src < n)
	{
		i = n - 1;
		while (i < n)
		{
			((unsigned char *)dest)[i] = ((unsigned char *)src)[i];
			i--;
		}
	}
	else
	{
		while (i < n)
		{
			((unsigned char *)dest)[i] = ((unsigned char *)src)[i];
			i++;
		}
	}
	return (dest);
}

char	*ft_lstclear_item(t_list **lst, int fd)
{
	t_list	*tmp;
	t_list	*step;

	tmp = *lst;
	while (tmp)
	{
		if (tmp->fd == fd)
			break ;
		step = tmp;
		tmp = tmp->next;
	}
	if (!tmp)
		return (NULL);
	if (tmp->buff)
		free(tmp->buff);
	if (tmp == *lst)
		*lst = tmp->next;
	else
		step->next = tmp->next;
	free(tmp);
	return (NULL);
}
