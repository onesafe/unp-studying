#include "unp.h"
#include "apueerror.h"

static int	read_cnt;
static char	*read_ptr;
static char	read_buf[MAXLINE];
int main(int argc, char **argv)
{
	int sockfd;
	struct sockaddr_in servaddr;
	if(argc != 2)
		err_quit("Usage: tcpcli <IPaddress>");
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(SERV_PORT);
	inet_pton(AF_INET, argv[1], &servaddr.sin_addr);

printf("start connecting...\n");
	connect(sockfd, (SA *)&servaddr, sizeof(servaddr));
	str_cli(stdin, sockfd);
	
	exit(0);
}

void str_cli(FILE *fp, int sockfd)
{
	char sendline[MAXLINE],recvline[MAXLINE];
	while(fgets(sendline, MAXLINE, fp)!=NULL)
	{
		write(sockfd, sendline, strlen(sendline));
		if(readline(sockfd, recvline, MAXLINE) == 0)
			err_quit("str_cli: server terminated prematurely");
		fputs(recvline, stdout);
	}
}

static ssize_t my_read(int fd, char *ptr)
{
	if(read_cnt <= 0)
	{
	again1:
		if((read_cnt = read(fd, read_buf, sizeof(read_buf))) < 0)
		{
			if(errno == EINTR)
				goto again1;
			return (-1);
		}else if (read_cnt == 0)
			return(0);
		read_ptr = read_buf;
	}
	read_cnt--;
	*ptr = *read_ptr++;
	return(1);

}

ssize_t readline(int fd, void *vptr, size_t maxlen)
{
	ssize_t n,rc;
	char	c,*ptr;
	
	ptr = vptr;
	for(n=1;n<maxlen;n++)
	{
		if((rc = my_read(fd, &c)) == 1)
		{
			*ptr++ = c;
			if(c=='\n')
				break;
		}else if (rc == 0)
		{
			*ptr = 0;
			return (n-1);
		}else
			return (-1);
	}
	*ptr = 0;
	return (n);
}
