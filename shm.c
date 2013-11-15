#include <sys/shm.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <stdio.h>
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

int main()
{
	key_t key;
	pid_t pid;
	int shmid,semid;
	char *shm_addr;
	union semum sem_val;
	struct sembuf sem_buf;

	if((key = ftok("/root/one", 2013))==-1)
		printf("ftok error");
	if((shmid = shmget(key, SHM_SIZE, IPC_CREAT|0666))==-1)
		printf("shmget error");
	if((semid = semget(key, 1, IPC_CREAT|0666))==-1)
		printf("create sem error");
	sem_val.val = 1;
	semctl(semid, 0, SETVAL, sem_val);
	
	if(pid=fork()<0)
		printf("fork error");
	else if(pid==0)
	{
		shm_addr = shmat(shmid,0,0);
		sem_buf.sem_num = 0;
		sem_buf.sem_op = -1;
		sem_buf.sem_flg = SEM_UNDO;
		semop(semid, &sem_buf, 1);

		memcpy(shm_addr, "hello, my name is y\n",20);
		printf("child: %s", shm_addr);
		printf("i am clild\n");
		sem_buf.sem_op = 1;
		semop(semid, &sem_buf, 1);
		shmdt(shm_addr);
	//	exit(0);
	}
	
	//waitpid(pid, NULL, 0);
	shm_addr = shmat(shmid, 0, 0);
		
	sem_buf.sem_num = 0;
	sem_buf.sem_op = -1;
	sem_buf.sem_flg = SEM_UNDO;

	semop(semid, &sem_buf, 1);
	memcpy(shm_addr, "hello, my name is w\n", 20);
	printf("parent: %s", shm_addr);
	printf("i am parent\n");
	sem_buf.sem_op = 1;

	semop(semid, &sem_buf, 1);
	semctl(semid, 0, IPC_RMID, 0);
	shmdt(shm_addr);
	shmctl(shmid, IPC_RMID, NULL);
	exit(0);
}
