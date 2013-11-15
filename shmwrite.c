#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>

typedef struct
{
	char name[8];
	int age;
}people;

int main(int argc, char **argv)
{
	int shm_id;
	key_t key;
	char temp[8];
	people *p_map;
	char pathname[30];
	int i=0;
	
	strcpy(pathname, "/tmp");
	key = ftok(pathname, 0x03);
	printf("key = %d\n", key);

	shm_id = shmget(key, 4096, IPC_CREAT|IPC_EXCL|0600);
	printf("shm_id = %d\n", shm_id);

	p_map = (people *)shmat(shm_id, NULL, 0);
	memset(temp, 0x00, sizeof(temp));
	strcpy(temp,"test");
	temp[4] = '0';
	for(i=0; i<3; i++)
	{
		temp[4]+=i;
		strncpy((p_map+i)->name, temp,5);
		(p_map+i)->age = 0+i;
	}
	shmdt(p_map);
	return 0;
}
