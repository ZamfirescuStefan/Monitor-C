#include "Monitor.h"

int MonitorInit(struct Monitor* m)
{
	if(pthread_mutex_init(&m->mutex, NULL))
	{
		perror(NULL);
		return errno;
	}
	if(pthread_cond_init(&m->condition, NULL))
	{
		perror(NULL);
		return errno;
	}
	
	return 0;
}

int MonitorWait(struct Monitor* m)
{
	if(pthread_cond_wait(&m->condition, &m->mutex))
	{
		perror(NULL);
		return errno;
	}
	
	return 0;
}

int MonitorSignal(struct Monitor* m)
{
	if(pthread_cond_signal(&m->condition))
	{
		perror(NULL);
		return errno;
	}
	
	return 0;
}

int MonitorDestroy(struct Monitor* m)
{
	if(pthread_mutex_destroy(&m->mutex))
	{
		perror(NULL);
		return errno;
	}
	if(pthread_cond_destroy(&m->condition))
	{
		perror(NULL);
		return errno;
	}
	
	return 0;
}
