#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include "Monitor.h"

int i, sc, sp, count, bufferSize, countProducers, countConsumers;
struct Monitor* m;

void add()
{
	printf("1 added\n");
	count++;
}

void get()
{
	printf("1 taken\n");
	count--;
}

void* producer(void* arg)
{
	int* k = (int*)arg;
	while((*k) > 0)		// cat timp sunt produse de adaugat
	{
		pthread_mutex_lock(&m->mutex);
		while(count == bufferSize)
			MonitorWait(m);		// astept cat timp raftul e plin
		add();	// adaug un produs
		(*k)--;
		MonitorSignal(m);
		pthread_mutex_unlock(&m->mutex);
	}
}

void* consumer(void* arg)
{
	int* k = (int*)arg;
	while((*k) > 0)		// cat timp mai sunt produse de luat
	{
		pthread_mutex_lock(&m->mutex);
		while(count == 0)
			MonitorWait(m);		// astept cat timp raftul e gol
		get();		// iau un produs
		(*k)--;
		MonitorSignal(m);
		pthread_mutex_unlock(&m->mutex);
	}
}

int main()
{
	scanf("%d", &bufferSize);
	
	scanf("%d", &countProducers);
	int prod[countProducers];
	sp = 0;
	for(i = 0; i < countProducers; i++)
	{
		scanf("%d", &prod[i]);
		sp += prod[i];
	}
	
	scanf("%d", &countConsumers);
	int cons[countConsumers];
	sc = 0;
	for(i = 0; i < countConsumers; i++)
	{
		scanf("%d", &cons[i]);
		sc += cons[i];
	}
	
	if(sp - sc > bufferSize)
	{
		printf("Buffer size too small\n");
		return 0;
	}
	if(sc > sp)
	{
		printf("Too many requests\n");
		return 0;
	}
	
	m = (struct Monitor*)malloc(sizeof(struct Monitor));
	MonitorInit(m);
	
	pthread_t pr[countProducers], con[countConsumers];
	
	for(i = 0; i < countProducers; i++)
	{
		int* aux = (int*)malloc(sizeof(int));
		*aux = prod[i];
		if(pthread_create(&pr[i], NULL, producer, (void*)aux))
		{
			perror(NULL);
			return errno;
		}
	}
	for(i = 0; i < countConsumers; i++)
	{
		int* aux = (int*)malloc(sizeof(int));
		*aux = cons[i];
		if(pthread_create(&con[i], NULL, consumer, (void*)aux))
		{
			perror(NULL);
			return errno;
		}
	}
	
	for(i = 0; i < countProducers; i++)
		if(pthread_join(pr[i], NULL))
		{
			perror(NULL);
			return errno;
		}
	for(i = 0; i < countConsumers; i++)
		if(pthread_join(con[i], NULL))
		{
			perror(NULL);
			return errno;
		}
	
	MonitorDestroy(m);

	return 0;
}
