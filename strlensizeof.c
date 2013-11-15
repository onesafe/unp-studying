#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

int main(void)
{
	int n = 0;
	char buf[512];
	char buf2[] = "wo shi yi ge ren\n";

	printf("%% ");
	while(fgets(buf, 512, stdin)!=NULL)
	{
		n = strlen(buf);
		printf("strlen(buf) = %d,", n);
		n = sizeof(buf);
		printf("sizeof(buf) = %d,", n);
		n = strlen(buf2);
		printf("strlen(buf2) = %d,", n);
		n = sizeof(buf2);
		printf("sizeof(buf2) = %d\n", n);
		write(STDOUT_FILENO, buf2, sizeof(buf2)-1);
	}
}
