#include "myMalloc.h"

void	*calloc_internal(size_t nmemb, size_t size)
{
	void	*ptr;

	if (nmemb != 0 && size > SIZE_MAX / nmemb)
		return (NULL);
	ptr = malloc_internal(nmemb * size);
	if (ptr)
		ft_bzero(ptr, nmemb * size);
	return (ptr);
}

void	*calloc(size_t nmemb, size_t size)
{
	void	*ret;

	pthread_mutex_lock(&g_mutex);
	ret = calloc_internal(nmemb, size);
	pthread_mutex_unlock(&g_mutex);
	return (ret);
}