#include "myMalloc.h"

static t_block *search_zone(t_zone *zone, void *ptr)
{
	t_block *block;

	block = FIRST_BLOCK(zone);
	while ((char *)block < ZONE_END(zone))
	{
		if (BLOCK_DATA(block) == ptr)
		{
			if (block->is_free)
				return (NULL);
			return (block);
		}
		block = NEXT_BLOCK(block);
	}
	return (NULL);
}

t_block *find_block(void *ptr, t_zone **out)
{
	t_zone	*lists[3];
	t_zone	*zone;
	int		i;

	lists[0] = g_heap.tiny;
	lists[1] = g_heap.small;
	lists[2] = g_heap.large;
	i = 0;
	while (i < 3)
	{
		zone = lists[i];
		while (zone)
		{
			if ((char *)ptr > (char *)zone && (char *)ptr < ZONE_END(zone))
			{
				*out = zone;
				return (search_zone(zone, ptr));
			}
			zone = zone->next;
		}
		i++;
	}
	return (NULL);
}

void	merge_with_next(t_zone *zone, t_block *block)
{
	t_block *after;
	t_block *next;

	next = NEXT_BLOCK(block);
	if ((char *)next >= ZONE_END(zone) || !next->is_free)
		return ;
	block->size += BLOCK_HDR + next->size;
	after = NEXT_BLOCK(block);
	if ((char *)after < ZONE_END(zone))
		after->prev = block;
}

t_block *find_free_block(t_zone *zone, size_t aligned, t_zone **out)
{
	t_block *block;

	while (zone)
	{
		block = FIRST_BLOCK(zone);
		while ((char *)block < ZONE_END(zone))
		{
			if (block->is_free && block->size >= aligned)
			{
				*out = zone;
				return (block);
			}
			block = NEXT_BLOCK(block);
		}
		zone = zone->next;
	}
	return (NULL);
}

void split_block(t_zone *zone, t_block *block, size_t aligned)
{
	t_block *new;
	t_block *after;

	if (block->size < aligned + MIN_SPLIT)
		return ;
	new = (t_block *)((char *)BLOCK_DATA(block) + aligned);
	new->prev = block;
	new->size = block->size - aligned - BLOCK_HDR;
	new->user_size = 0;
	new->is_free = 1;
	block->size = aligned;
	after = NEXT_BLOCK(new);
	if ((char *)after < ZONE_END(zone))
		after->prev = new;
}