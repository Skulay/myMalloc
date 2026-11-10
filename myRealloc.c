#include "myMalloc.h"

void    *realloc_internal(void *ptr, size_t size)
{

}

void	*realloc(void *ptr, size_t size)
{
	void	*ret;

	pthread_mutex_lock(&g_mutex);
	ret = realloc_internal(ptr, size);
	pthread_mutex_unlock(&g_mutex);
	return (ret);
}