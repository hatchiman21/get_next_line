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
	while (i++ < 3)
    	printf("%d\n",printf("%s",get_next_line(fd)));
    return 0;
}
