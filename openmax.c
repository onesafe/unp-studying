#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
	int	i = 0;
	i = sysconf(_SC_OPEN_MAX);
	printf("open_max = %d\n", i);
}
