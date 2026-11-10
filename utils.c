#include "myMalloc.h"

size_t	zone_size(size_t max_alloc)
{
	size_t	page;
	size_t	need;

	page = getpagesize();
	need = sizeof(t_zone) + MIN_ALLOCS * (sizeof(t_block) + max_alloc);
	return ((need + page - 1) / page * page);
}
