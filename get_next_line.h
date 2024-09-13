#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 32
# endif

# include <unistd.h>
# include <stdlib.h>

typedef struct s_next_line
{
	int					fd;
	char				*buffer;
	struct s_next_line	*next;
}	t_next_line;

size_t	ft_strlen(const char *s);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strdup(const char *s);
char	*ft_substr(char const *s, unsigned int start, size_t len);

void	*ft_memmove(void *dest, const void *src, size_t n);
char	*get_next_line(int fd);

#endif
