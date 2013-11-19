#include <stdio.h>

int main(void)
{
	FILE*	fp;
	int	result;
	int	c;
	fpos_t	pos1,pos2;

	if((fp = fopen("a.txt", "r+")) == NULL)
	{
		result = -1;
		perror("fopen");
		goto FINALLY;
	}

	if((c = fgetc(fp)) != -1)
	{
		printf("read c:%c\n", c);
	}

	if((c = fgetc(fp)) != -1)
	{
		printf("read c:%c\n", c);
	}

	if(fgetpos(fp, &pos1) != 0)
	{
		result = -1;
		perror("fgetpos");
		goto FINALLY;
	}

	printf("position:%ld\n", pos1);

	if((c = fgetc(fp)) != -1)
	{
		printf("read c:%c\n", c);
	}

	if((c = fgetc(fp)) != -1)
	{
		printf("read c:%c\n", c);
	}

	if(fgetpos(fp, &pos2) != 0)
	{
		result = -1;
		perror("fgetpos");
		goto FINALLY;
	}
	
	printf("position:%ld\n", pos2);

	if(fsetpos(fp, &pos1) != 0)
	{
		result = -1;
		perror("fsetpos");
		goto FINALLY;
	}

	if(fgetpos(fp, &pos2) != 0)
	{
		result = -1;
		perror("fgetpos");
		goto FINALLY;
	}
	
	printf("position:%ld\n", pos2);

FINALLY:
	if(fp != NULL)
	{
		fclose(fp);
	}

	return result;
}
