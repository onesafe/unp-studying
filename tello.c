#include <stdio.h>

int main(void)
{
	FILE	*fp;
	int	result;
	int	c;

	if((fp = fopen("a.txt", "r+")) == NULL)
	{
		result = -1;
		perror("fopen");
		goto FINALLY;
	}

	printf("position:%ld\n", ftell(fp));

	if((c = fgetc(fp)) != -1)
	{
		printf("read c:%c\n", c);
	}

	if((c = fgetc(fp)) != -1)
	{
		printf("read c:%c\n", c);
	}

	printf("position:%ld\n", ftello(fp));

	if((fseeko(fp, 3, SEEK_CUR)) != 0)
	{
		result = -1;
		perror("fseeko");
		goto FINALLY;
	}

	printf("position:%ld\n", ftell(fp));

FINALLY:
	if(fp != NULL)
	{
		close(fp);
	}

	return result;
}
