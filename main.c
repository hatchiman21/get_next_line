#include "get_next_line.h"
#include <stdio.h>
#include <fcntl.h>

int main()
{
    char *res;
    int fd;
	int	i;

	i = 0;
    fd = open("test.txt", O_RDWR);
	while (i++ < 5)
	{
		res = get_next_line(fd);
    	printf("%d : %s",i,res);
		free(res);
	}
    return 0;
}
