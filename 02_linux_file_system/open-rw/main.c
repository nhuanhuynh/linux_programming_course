#include <stdio.h>
#include<string.h> 
#include <fcntl.h>
#include <unistd.h>

void main(void)
{
    int fd; //file descrtiptor
    int num_write;
    int off_set;

    char buf[] = "Hello World\n";

    fd = open("hello.txt", O_RDWR | O_CREAT, 0665); // 110 110 101

    if (-1 == fd)
    {
        printf("Open failed!!!");
        return;
    }

    num_write = write(fd, buf, sizeof(buf));

    printf("Wrote %d bytes into hello.txt\n", num_write);

    off_set = lseek(fd, -5, SEEK_END); //reposition the cursor
    printf("off_set: %d\n", off_set);

    num_write = write(fd, "AAAAAAAAAAAA", strlen("AAAAAAAAAAAA"));
    printf("Wrote %d bytes into hello.txt\n", num_write);
    
    close(fd);
    return;
}