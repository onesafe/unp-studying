#include <sys/shm.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

#define SHM_SIZE 1024

union semum
{
	int val;
	struct semid_ds *buf;
	unsigned short *array;
};

typedef struct
{
	int age;
	char name[10];
}people;

int main()
{
	key_t key;
	int shmid,semid;
	union semum sem_val;
	struct sembuf sem_buf;
	char buf[1024];
	char temp[10];
	people *p;
	int i=0;
	
	key = ftok("/root/one", 2013);
	shmid = shmget(key, SHM_SIZE, IPC_CREAT|0666);
	semid = semget(key, 1, IPC_CREAT|0666);

	printf("key = %d\n", key);
	printf("shmid = %d\n", shmid);
	printf("semid = %d\n", semid);

	sem_val.val = 1;
	semctl(semid, 0, SETVAL, sem_val);

	p = (people *)shmat(shmid, 0, 0);
	
//P()
	sem_buf.sem_num = 0;
	sem_buf.sem_op = -1;
	sem_buf.sem_flg = SEM_UNDO;
	semop(semid, &sem_buf, 1);

	memset(temp, 0x00, sizeof(temp));
	strcpy(temp, "wang");
	temp[4] = '0';
	for(i=0; i<3; i++)
	{
		temp[4]+=1;
		strncpy((p+i)->name, temp, 5);
		(p+i)->age=20+i;
	}

	//strcpy(buf, "Can you hear me? I am servers!\n");
	//memcpy(shm_addr, buf, strlen(buf));
//V()	
	sem_buf.sem_op = 1;
	semop(semid, &sem_buf, 1);
	shmdt(p);	
	return 0;
}
