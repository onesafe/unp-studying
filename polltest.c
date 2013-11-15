#include <assert.h>
#include <ctype.h>
#include <errno.h>
#include <float.h>
#include <limits.h>
#include <locale.h>
#include <math.h>
#include <netinet/in.h>
#include <setjmp.h>
#include <signal.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/file.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/times.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>
#include <signal.h>
#include <unistd.h>
#include <sys/stat.h>

char *Int2Buf(int value, char *buf, unsigned int len);
char *BuildFile(const char *file);
char *BuildPath(const char *path);

int main(void)
{
/*
 * 	char *file;
	file = BuildPath("./wang/yi/ping");
	printf("%s\n", file);
*/
	char p[50];
	char *buf;
	buf = Int2Buf(56789, p, 10);
	printf("%s\n", buf);
}

/*
 * 递归建立目录
 *
 * @file 入参 含全路径，文件名
 * 	例：/wang/yi/ping
 * 	会建立/wang/yi目录
 *
 * 返回@file
 */

char *BuildFile(const char *file)
{
	char *p = NULL;
	char buf[512+19] = {0};
	
	for( p=(char *)file; abs((p=strchr(p, '/'))-file) < strlen(file); p++)
	{
		memset(buf, 0, sizeof(buf));
		memcpy(buf, file, p-file);
		mkdir(buf, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
	}

	return (char *)file;
}

/*
 * 递归建立目录
 *
 * @path 入参 含全路径名，不包括文件名
 * 	例：/wang/yi/ping
 * 	会建立/wang/yi/ping三个目录
 *
 * 返回@path
 */

char *BuildPath(const char *path)
{
	BuildFile(path);
	mkdir(path, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
	
	return (char *)path;
}

/*
 * 把数字转化成指定长度的buf，位数不足前补0
 *
 * @value 入参
 * @buf   出参
 * @len   入参
 *
 * 返回转化后的buf
 */

char *Int2Buf(int value, char *buf, unsigned int len)
{
	char tmpbuf[64] = {0};
	sprintf(tmpbuf, "%0*d", len, value);
	memcpy(buf, tmpbuf, len);
	buf[len] = '\0';
	return buf;
}
