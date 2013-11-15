#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

static char buf[5];
int main(void)
{
	int n;
	char *p;
	FILE *fp;
	char line[1000];

	if((fp = fopen("/root/gitwyp/tcpcli01.c", "r")) == NULL)
		printf("fopen error\n");
	if(setvbuf(fp, buf, _IOLBF, 5) != 0)
		printf("setvbuf error\n");

	fread(line, 1000, fp);
	fwrite(line, stdout);
	fgets(line, 1000, fp);
	fputs(line, stdout);
//	while(fgets(line, 1000, fp) != NULL)
//		fputs(line, stdout);
	exit(0); 
	
}
