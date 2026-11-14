#include "myMalloc.h"

static void	*keep_block(t_zone *zone, t_block *block, size_t size)
{
	t_block	*next;

	if (zone->type != TYPE_LARGE)
	{
		split_block(zone, block, ALIGN(size));
		next = NEXT_BLOCK(block);
		if ((char *)next < ZONE_END(zone) && next->is_free)
			merge_with_next(zone, next);
	}
	block->user_size = size;
	return (BLOCK_DATA(block));
}

void	*realloc_internal(void *ptr, size_t size)
{
	t_block	*block;
	t_zone	*zone;
	void	*new;
	size_t	copy;

	if (!ptr)
		return (malloc_internal(size));
	if (size == 0)
	{
		free_internal(ptr);
		return (NULL);
	}
	block = find_block(ptr, &zone);
	if (!block)
		return (NULL);
	if (get_type(size) == (int)zone->type && ALIGN(size) <= block->size)
		return (keep_block(zone, block, size));
	new = malloc_internal(size);
	if (!new)
		return (NULL);
	copy = block->user_size;
	if (size < copy)
		copy = size;
	ft_memcpy(new, ptr, copy);
	free_internal(ptr);
	return (new);
}

void	*realloc(void *ptr, size_t size)
{
	void	*ret;

	pthread_mutex_lock(&g_mutex);
	ret = realloc_internal(ptr, size);
	pthread_mutex_unlock(&g_mutex);
	return (ret);
}