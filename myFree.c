#include "myMalloc.h"

void	free(void *ptr)
{
	pthread_mutex_lock(&g_mutex);
    free_internal(ptr);
    pthread_mutex_unlock(&g_mutex);
}