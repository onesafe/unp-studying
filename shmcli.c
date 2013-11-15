#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/sem.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define SHM_SIZE 1024

typedef struct
{
	int age;
	char name[10];
}people;

int main()
{
	key_t key;
	int shmid, semid;
	struct sembuf sem_buf;
	people *p;
	int i=0;

	key = ftok("/root/one", 2013);
	shmid = shmget(key, 0, 0666);
	semid = semget(key, 1, 0666);
	
	printf("key = %d\n", key);
	printf("shmid = %d\n", shmid);
	printf("semid = %d\n", semid);
	
	p = (people *)shmat(shmid, 0, 0);
	
//P()
	sem_buf.sem_num = 0;
	sem_buf.sem_op = -1;
	sem_buf.sem_flg = SEM_UNDO;
	semop(semid, &sem_buf, 1);
	
	for(i=0; i<3; i++)
	{
		printf("name:%s\n",(*(p+i)).name);
		printf("age %d\n", (*(p+i)).age);
	}

	//printf("cli recved==>: %s \n", shm_addr);
//V()
	sem_buf.sem_op = 1;
	semop(semid, &sem_buf, 1);

	shmdt(p);
//	semctl(semid, 0, IPC_RMID, 0);
//	shmctl(shmid, IPC_RMID, NULL);
	return 0;
}
