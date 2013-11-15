#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main()
{
	int n = 0;
	char buf[102];
	if((n = read(STDIN_FILENO, buf, 102)) > 0)
		printf("n = %d\n", n);

}
