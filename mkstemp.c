#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(void)
{
	int	n;
	int	fd;
	char	line[100];
	char	temp_file[]="wyp-XXXXXX";

	if((fd = mkstemp(temp_file)) == -1)
	{
		printf("creat temp file failed\n");
		exit(1);
	}

	unlink(temp_file);
	


	if((write(fd, "hello nihao\n", 13)) == -1)
		printf("first write error\n");
	
	if(lseek(fd, 0, SEEK_SET) == -1)
		printf("lseek error\n");

	if((n = read(fd, line, sizeof(line))) < 0)
		printf("read error");

	
	if(write(STDOUT_FILENO, line, n) != n)
		printf("second write error\n");

	close(fd);

	return 0;
}
