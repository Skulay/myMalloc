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
	
}

size_t	zone_size(size_t max_alloc)
{
	size_t	page;
	size_t	need;

	page = page_size();
	need = sizeof(t_zone) + MIN_ALLOCS * (sizeof(t_block) + max_alloc);
	return ((need + page - 1) / page * page);
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

}