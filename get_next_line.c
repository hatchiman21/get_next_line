#include "get_next_line.h"
#include <string.h>
#include <stdio.h>

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*res;
	int		i;
	int		j;

	i = 0;
	j = 0;
	res = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!res)
		return (NULL);
	while (s1[i])
	{
		res[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		res[i + j] = s2[j];
		j++;
	}
	res[i + j] = '\0';
	return (res);
}

char	*merge(char *res, char *word)
{
	char	*temp;

	temp = res;
	res = ft_strjoin(temp, word);
	free (temp);
	return (res);
}

int	ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while ((i - 1 < 0 || s[i - 1]))
	{
		if (s[i] == (char)c)
			return (i);
		i++;
	}
	return (-1);
}

t_next_line	*get_buffer(t_next_line **all_fd, int fd)
{
	t_next_line	*check;
	t_next_line	*new;

	check = *all_fd;
	while (check)
	{
		if (check->fd = fd)
			return (check);
		check = check->next;
	}
	
	new = (t_next_line *)malloc(sizeof(t_next_line));
	if (!new)
		return (NULL);
	new->fd = fd;
	new->buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE));
	if (!(new->buffer))
	{
		free(new->buffer);
		return (NULL);
	}
	new->next = *all_fd;
	return (new);
}

char	*get_next_line(int fd)
{
	static t_next_line *all_fd;
	t_next_line 		*temp;
	int					i;
	char				*res;
	char				*t;

	i = -1;
	temp = get_buffer(all_fd, fd);
	//if (all_fd->buffer)
		i = ft_strchr(all_fd->buffer, '\n');
	if (i != -1)
	{
		t = all_fd->buffer;
		res = ft_substr(t, 0, i);
		all_fd->buffer = (t + i);
		return (res);
	}
	return (res);
}
