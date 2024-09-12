#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>

typedef struct s_next_line
{
	int		fd;
	char	*buffer;
	struct	s_next_line next;
} t_next_line;


# ifndef BUFFER_SIZE
# 	define BUFFER_SIZE 32
# endif

char	*get_next_line(int fd);
char	**ft_split(char const *s, char c);
char	*ft_strdup(const char *s);
char	*ft_substr(char const *s, unsigned int start, size_t len);

#endif
