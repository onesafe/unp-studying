#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

char buf1[]="abcdefghij";
char buf2[]="ABCDEFGHIJ";

int main()
{
	int fd;
	if((fd = open("file.hole", O_RDWR|O_CREAT|O_TRUNC,  0666))<0)
		perror("create error");
	if(write(fd, buf1, 10) != 10)
		perror("write error");
	if(lseek(fd, 16388, SEEK_SET) == -1)
		perror("lseek error");
	if(write(fd, buf2, 10) != 10)
		perror("write error");
	exit(0);
}
