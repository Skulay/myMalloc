#include "myMalloc.h"

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

size_t	round_to_page(size_t n)
{
	size_t	page;

	page = page_size();
	return ((n + page - 1) / page * page);
}

size_t	zone_size(size_t max_alloc)
{
	size_t	need;

	need = ZONE_HDR + MIN_ALLOCS * (BLOCK_HDR + max_alloc);
	return (round_to_page(need));
}

int	get_type(size_t size)
{
	if (size <= TINY_MAX)
		return (TYPE_TINY);
	if (size <= SMALL_MAX)
		return (TYPE_SMALL);
	return (TYPE_LARGE);
}

t_zone	**get_list(int type)
{
	// t_heap	g_heap = {NULL, NULL, NULL};

	// typedef struct s_heap
	// {
	// 	t_zone			*tiny;
	// 	t_zone			*small;
	// 	t_zone			*large;
	// }	t_heap;

	if (type == TYPE_TINY)
		return (&g_heap.tiny);
	if (type == TYPE_SMALL)
		return (&g_heap.small);
	return (&g_heap.large);
}