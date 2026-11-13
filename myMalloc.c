#include "myMalloc.h"

static void	*alloc_small(size_t size, int type)
{
	size_t	aligned;
	size_t	max;
	t_zone	*zone;
	t_block	*block;

	aligned = ALIGN(size);
	block = find_free_block(*get_list(type), aligned, &zone);
	if (!block)
	{
		max = TINY_MAX;
		if (type == TYPE_SMALL)
			max = SMALL_MAX;
		zone = create_zone(type, zone_size(max));
		if (!zone)
			return (NULL);
		block = FIRST_BLOCK(zone);
	}
	split_block(zone, block, aligned);
	block->is_free = 0;
	block->user_size = size;
	return (BLOCK_DATA(block));
}

static void	*alloc_large(size_t size)
{
	t_zone	*zone;
	t_block	*block;

	zone = create_zone(TYPE_LARGE, round_to_page(ZONE_HDR + BLOCK_HDR + ALIGN(size)));
	if (!zone)
		return (NULL);
	block = FIRST_BLOCK(zone);
	block->is_free = 0;
	block->user_size = size;
	return (BLOCK_DATA(block));
}

void	*malloc_internal(size_t size)
{
	int	type;

	if (size == 0)
		size = 1;
	if (size > SIZE_MAX - ZONE_HDR - BLOCK_HDR - page_size() - ALIGNMENT)
		return (NULL);
	type = get_type(size);
	if (type == TYPE_LARGE)
		return (alloc_large(size));
	return (alloc_small(size, type));
}

void	*malloc(size_t size)
{
	void	*ret;

	pthread_mutex_lock(&g_mutex);
	ret = malloc_internal(size);
	pthread_mutex_unlock(&g_mutex);
	return (ret);
}