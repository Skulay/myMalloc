#include "myMalloc.h"

void	*malloc(size_t size)
{
	pthread_mutex_lock(&g_mutex);
    malloc_internal(ptr);
    pthread_mutex_unlock(&g_mutex);
}