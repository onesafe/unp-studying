#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <signal.h>

static void sig_pipe(int);

int main(void)
{
	int	n,fd1[2],fd2[2];
	pid_t	pid;
	char	line[512];
	
	if(signal(SIGPIPE, sig_pipe) == SIG_ERR)
		fprintf(stderr,"signal error:%d", errno);
	if(pipe(fd1) < 0 || pipe(fd2) < 0)
		fprintf(stderr,"pipe error:%d", errno);
	if((pid = fork()) < 0)
		fprintf(stderr,"fork error:%d", errno);
	else if(pid > 0)
	{
		close(fd1[0]);
		close(fd2[1]);
		while(fgets(line, 512, stdin) != NULL)
		{
			n = strlen(line);
			if(write(fd1[1], line, n) != n)
				fprintf(stderr,"write error to pipe:%d", errno);
			if((n = read(fd2[0], line, 512)) < 0)
				fprintf(stderr,"read error:%d", errno);
			if(n == 0)
			{
				printf("child close pipe");
				break;
			}
			line[n] = 0;
			if(fputs(line, stdout) == EOF)
				printf("fputs error");
		}
		if(ferror(stdin))
			printf("fgets error on stdin\n");
		exit(0);
	}
	else
	{
		close(fd1[1]);
		close(fd2[0]);
		if(fd1[0] != STDIN_FILENO)
		{
			if(dup2(fd1[0], STDIN_FILENO) != STDIN_FILENO)
				printf("dup2 error to stdin");
			close(fd1[0]);
		}
		if(fd2[1] != STDOUT_FILENO)
		{
			if(dup2(fd2[1], STDOUT_FILENO) != STDOUT_FILENO)
				printf("dup2 error to stdout");
			close(fd2[1]);
		}
		if(execl("./add2", "add2", (char *)0)<0)
			printf("execl error");
	}
	exit(0);
}

static void sig_pipe(int signo)
{
	printf("SIGPIPE caught\n");
	exit(1);
}

