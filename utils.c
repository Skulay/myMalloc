#include "myMalloc.h"

t_heap	g_heap = {NULL, NULL, NULL};
pthread_mutex_t	g_mutex = PTHREAD_MUTEX_INITIALIZER;

size_t	page_size(void)
{
#ifdef __APPLE__
	return ((size_t)getpagesize());
#else
	long	size;

	size = sysconf(_SC_PAGESIZE);
	if (size <= 0)
		return (4096);
	return ((size_t)size);
#endif
}

size_t	zone_size(size_t max_alloc)
{
	size_t	page;
	size_t	need;

	page = page_size();
	need = sizeof(t_zone) + MIN_ALLOCS * (sizeof(t_block) + max_alloc);
	return ((need + page - 1) / page * page);
}
