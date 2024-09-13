#include "get_next_line.h"

void	ft_lstclear(t_next_line **lst)
{
	t_next_line	*temp;
	t_next_line	*temp2;

	if (!*lst)
		return ;
	temp = *lst;
	while (temp)
	{
		free (temp->buffer);
		temp2 = temp;
		temp = temp->next;
		free (temp2);
	}
	*lst = NULL;
}

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
	while ((i - 1 < 0 || s[i - 1]))
	{
		if (s[i] == (char)c)
			return (i + 1);
		i++;
	}
	return (-1);
}

static char	*get_result(int fd, t_next_line *current, int i, char *res, t_next_line *all)
{
	char	*buff;
	int		bytes_read;

	bytes_read = 1;
	while (i == -1 && bytes_read > 0)
	{
		bytes_read = read(fd, current->buffer, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free (res);
			return (NULL);
		}
		if (bytes_read == 0)
		{
			ft_lstclear(&all);
			return (res);
		}
		current->buffer[BUFFER_SIZE] = '\0';
		buff = current->buffer;
		i = ft_strchr(buff, '\n');
		if (i != -1)
		{
			res = merge(res, ft_substr(buff, 0, i));
			current->buffer = ft_memmove(buff, (buff + i),
				ft_strlen(buff + i) + 1);
			return (res);
		}
		res = merge(res, ft_substr(buff, 0, ft_strlen(buff)));
	}
	return (res);
}

static t_next_line	*get_buffer(t_next_line **all_fd, int fd)
{
	t_next_line	*check;
	t_next_line	*new;

	check = *all_fd;
	while (check)
	{
		if (check->fd == fd)
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
		free(new->buffer);
		return (NULL);
	}
	new->buffer[0] = '\0';
	new->next = *all_fd;
	*all_fd = new;
	return (new);
}

char	*get_next_line(int fd)
{
	static t_next_line	*all_fd;
	t_next_line			*current;
	int					i;
	char				*res;

	i = -1;
	if (fd == -1)
		return (NULL);
	res = (char *)malloc(sizeof(char));
	current = get_buffer(&all_fd, fd);
	res[0] = '\0';
	if (current->buffer[0] != '\0')
		i = ft_strchr(current->buffer, '\n');
	if (i != -1)
	{
		res = ft_substr(current->buffer, 0, i);
		current->buffer = ft_memmove(current->buffer, (current->buffer + i),
				ft_strlen(current->buffer + i) + 1);
		return (res);
	}
	res = get_result(fd, current, i, res, all_fd);
	return (res);
}
