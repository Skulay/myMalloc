#include "myMalloc.h"

// a finir quand malloc rseras finis mais ca devrait ressembler a ce delire

// void	calloc_internal(size_t nmemb, size_t size)
// {
// 	malloc_internal(ptr);
// 	bzero(ptr);
// 	return (ptr);
// }

void	*calloc(size_t nmemb, size_t size)
{
	pthread_mutex_lock(&g_mutex);
	calloc_internal(nmemb, size);
	pthread_mutex_unlock(&g_mutex);
}