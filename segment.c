#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

void func()
{
	char *p = NULL;
	*p = 3;
}

main()
{
	func();
	return;
}
