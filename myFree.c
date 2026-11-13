#include "myMalloc.h"

// free et fusionner directement les block vide entreeux apres un call de free

static void	release_if_empty(t_zone *zone)
{
	t_block	*first;

	first = FIRST_BLOCK(zone);
	if (!first->is_free || (char *)NEXT_BLOCK(first) < ZONE_END(zone))
			return ;
	if (!zone->prev && !zone->next)
			return ;
	remove_zone(get_list(zone->type), zone);
}

void	free_internal(void *ptr)
{
	t_zone  *zone;
	t_block *block;

	if (!ptr)
			return ;
	block = find_block(ptr, &zone);
	if (!block)
			return ;
	if (zone->type == TYPE_LARGE)
	{
			remove_zone(&g_heap.large, zone);
			return ;
	}
	block->is_free = 1;
	block->user_size = 0;
	merge_with_next(zone, block);
	if (block->prev && block->prev->is_free)
			merge_with_next(zone, block->prev);
	release_if_empty(zone);
}

void	free(void *ptr)
{
	pthread_mutex_lock(&g_mutex);
	free_internal(ptr);
	pthread_mutex_unlock(&g_mutex);
}