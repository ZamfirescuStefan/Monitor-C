#ifndef MonitorLib
#define MonitorLib

#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <pthread.h>

struct Monitor
{
	pthread_mutex_t mutex;
	pthread_cond_t condition;
};

int MonitorInit(struct Monitor* m);
int MonitorWait(struct Monitor* m);
int MonitorSignal(struct Monitor* m);
int MonitorDestroy(struct Monitor* m);

#endif
