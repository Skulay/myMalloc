#include "myMalloc.h"

// a finir quand malloc rseras finis mais ca devrait ressembler a ce delire

// void	calloc_internal(void *ptr)
// {
// 	malloc_internal(ptr);
// 	bzero(ptr);
// 	return (ptr);
// }

void	calloc(void *ptr)
{
	pthread_mutex_lock(&g_mutex);
	calloc_internal(ptr);
	pthread_mutex_unlock(&g_mutex);
}