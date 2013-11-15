#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/ipc.h>

int main(void)
{
	int	n,int1,int2;
	char	line[512];
	
	while((n=read(STDIN_FILENO,line,512))>0)
	{
		line[n]=0;
		if(sscanf(line,"%d%d", &int1,&int2)==2)
		{
			sprintf(line, "%d\n", int1+int2);
			n = strlen(line);
			if(write(STDOUT_FILENO,line,n)!=n)
				fprintf(stderr,"write error:%d",errno);
		}
		else
		{
			if(write(STDOUT_FILENO, "invalid args\n", 13)!=13)
				fprintf(stderr,"write error:%d",errno);
		}
	}
	exit(0);
}
