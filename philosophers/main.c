#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

int mails = 0;
pthread_mutex_t mutex;

void* print_n(void* n)
{
	pthread_mutex_lock(&mutex);
	printf("Loop number %d\n",*(int*)n);
	pthread_mutex_unlock(&mutex);
}

void* routine()
{
	pthread_mutex_lock(&mutex);
	for (int i = 0; i < 100000; i++)
		mails++; 
	pthread_mutex_unlock(&mutex);
}

int main(int argc, char* argv[])
{
	pthread_t th[4];
	int i;
	int a[4];
	pthread_mutex_init(&mutex, NULL);
	for (i = 0; i < 4; i++)
	{
		a[i] = i;
		if (pthread_create(&th[i], NULL, &print_n, &a[i]) != 0)
			return(1);
	}
	for (i = 0; i < 4; i++)
	{
		if (pthread_join(th[i], NULL) != 0)
			return(1);
	}
	pthread_mutex_destroy(&mutex);
	return 0;
} 