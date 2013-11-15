#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/ipc.h>

#define DEF_PAGER "/bin/more"
#define MAXLINE 512
int main(int argc, char *argv[])
{
	int	n;
	int	fd[2];
	pid_t	pid;
	char	*pager,*argv0;
	char	line[MAXLINE];
	FILE	*fp;
	
	if(argc != 2)
		printf("Usage: a.out <pathname>");
	if((fp=fopen(argv[1],"r"))==NULL)
		printf("can't open %s", argv[1]);
	if(pipe(fd)<0)
		fprintf(stderr,"pipe error:%d\n", errno);
	if((pid=fork())<0)
	{
		fprintf(stderr,"fork error:%d\n", errno);
	}
	else if(pid>0)
	{
		close(fd[0]);
		while(fgets(line, MAXLINE, fp)!=NULL)
		{
			n = strlen(line);
			if(write(fd[1],line,n) != n)
				fprintf(stderr, "write error:%d\n", errno);
		}
		if(ferror(fp))
			fprintf(stderr, "fgets error:%d\n", errno);
		close(fd[1]);
		if(waitpid(pid, NULL, 0)<0)
			fprintf(stderr, "waitpid error:%d\n", errno);
		exit(0);
	}
	else
	{
		close(fd[1]);
		if(fd[0]!=STDIN_FILENO)
		{
			if(dup2(fd[0],STDIN_FILENO)!=STDIN_FILENO)
				printf("dup2 error to stdin");
			close(fd[0]);
		}

		if((pager=getenv("PAGER"))==NULL)
			pager=DEF_PAGER;
		if((argv0 = strrchr(pager, '/'))!=NULL)
			argv0++;
		else
			argv0 = pager;
		
		if(execl(pager, argv0,(char *)0)<0)
			printf("execl error ");
	}
	exit(0);
}
