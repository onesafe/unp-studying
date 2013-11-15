#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

struct foo
{
	int a,b,c,d;
}w;


void printfoo(const char *s, const struct foo *fp)
{
	printf(s);
	printf(" structure at 0x%x\n", (unsigned)fp);
	printf(" foo.a = %d\n", fp->a);
	printf(" foo.b = %d\n", fp->b);
	printf(" foo.c = %d\n", fp->c);
	printf(" foo.d = %d\n", fp->d);
}

void *thr_fn1(void *arg)
{
	pthread_t  tid;
	tid = pthread_self();
	printf("thread 1: ID is %u\n", (unsigned int)tid);
	printfoo("thread 1:\n", &w);
	w.a = 500;
	w.b = 600;
	w.c = 700;
	w.d = 800;
	pthread_exit((void *)&w);
}

void *thr_fn2(void *arg)
{
	pthread_t tid;
	tid = pthread_self();
	printf("thread 2: ID is %u\n", (unsigned int)tid);
	pthread_exit((void *)0);
}

int main(void)
{
	int err;
	pthread_t tid1, tid2;
	struct foo *fp;
	w.a = 1; w.b = 2; w.c = 3; w.d = 4;

	err = pthread_create(&tid1, NULL, thr_fn1, NULL);
	if(err != 0)
		printf("can't create thread 1: %s\n", strerror(err));
	err = pthread_join(tid1, (void *)&fp);
	if(err != 0)
		printf("can't join with thread 1: %s\n", strerror(err));
	sleep(1);
	printf("parent starting second thread\n");
	err = pthread_create(&tid2, NULL, thr_fn2, NULL);
	if( err != 0)
		printf("can't create thread 2: %s\n", strerror(err));
	sleep(1);
	printfoo("parent: \n", fp);
	return 0;

}
