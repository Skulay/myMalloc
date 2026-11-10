#include "myMalloc.h"

void    *malloc_internal(size_t size)
{

}

void	*malloc(size_t size)
{
	void	*ret;

	pthread_mutex_lock(&g_mutex);
	ret = malloc_internal(size);
	pthread_mutex_unlock(&g_mutex);
	return (ret);
}