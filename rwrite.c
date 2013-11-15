#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

int main()
{
	int n;
	char buf[512];
	while((n = read(STDIN_FILENO, buf, 512)) > 0)
	{
		if(write(STDOUT_FILENO, buf, n) != n)
			perror("write error");
	}
	if(n < 0)
		perror("read error");
	exit(0);
}
