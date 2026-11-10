#include "myMalloc.h"

void    *realloc_internal(void *ptr, size_t size)
{

}

void	*realloc(void *ptr, size_t size)
{
	pthread_mutex_lock(&g_mutex);
	realloc_internal(ptr);
	pthread_mutex_unlock(&g_mutex);
}