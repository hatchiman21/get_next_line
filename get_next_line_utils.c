#include "get_next_line.h"

char	*ft_strdup(const char *s)
{
	char	*res;
	int		i;

	i = 0;
	while (s[i])
		i++;
	res = (char *)malloc(sizeof(char) * (i + 1));
	if (res == NULL)
		return (NULL);
	i = 0;
	while (s[i])
	{
		res[i] = s[i];
		i++;
	}
	res[i] = '\0';
	return (res);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	unsigned int	i;
	char			*res;

	i = 0;
	if (start > ft_strlen(s))
		return (ft_strdup(""));
	while (s[i])
		i++;
	if (i - start > len)
		res = (char *)malloc(sizeof(char) * len + 1);
	else
		res = (char *)malloc(sizeof(char) * (i - start + 1));
	if (res == NULL)
		return (NULL);
	i = 0;
	while (s[start] && i < len)
		res[i++] = s[start++];
	res[i] = '\0';
	return (res);
}
