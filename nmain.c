#include "get_next_line.h"
#include <stdio.h>
#include <fcntl.h>
int main(){
    
    char* fileName = "test.txt";

    int fd = open(fileName, O_RDWR);
    
    if(fd == -1){
        printf("\nError Opening File!!\n");
        exit(1);
    }
    else{
        printf("\nFile %s opened sucessfully!\n", fileName);
    }

    char buffer[1024];

    int bytesRead = read(fd, buffer, sizeof(buffer));

    printf("%d bytes read!\n", bytesRead);
    printf("File Contents: %s\n", buffer);

    return 0;
}