#include "myMalloc.h"

static void	put_addr(void *ptr)
{
	ft_putstr_fd("0x", 1);
	ft_putbighex((unsigned long)ptr);
}

static size_t	print_zone(t_zone *zone)
{
	char	*names[3] = {"TINY : ", "SMALL : ", "LARGE : "};
	t_block	*block;
	char	*start;
	size_t	total;

	ft_putstr_fd(names[zone->type], 1);
	put_addr(zone);
	ft_putstr_fd("\n", 1);
	total = 0;
	block = FIRST_BLOCK(zone);
	while ((char *)block < ZONE_END(zone))
	{
		if (!block->is_free)
		{
			start = BLOCK_DATA(block);
			put_addr(start);
			ft_putstr_fd(" - ", 1);
			put_addr(start + block->user_size);
			ft_putstr_fd(" : ", 1);
			ptf_putnbr(block->user_size);
			ft_putstr_fd(" bytes\n", 1);
			total += block->user_size;
		}
		block = NEXT_BLOCK(block);
	}
	return (total);
}

static int	lowest_zone(t_zone *cur[3])
{
	int	min;
	int	i;

	min = -1;
	i = 0;
	while (i < 3)
	{
		if (cur[i] && (min == -1 || cur[i] < cur[min]))
			min = i;
		i++;
	}
	return (min);
}

void	show_alloc_mem_internal(void)
{
	t_zone	*cur[3];
	size_t	total;
	int		i;

	cur[0] = g_heap.tiny;
	cur[1] = g_heap.small;
	cur[2] = g_heap.large;
	total = 0;
	i = lowest_zone(cur);
	while (i != -1)
	{
		total += print_zone(cur[i]);
		cur[i] = cur[i]->next;
		i = lowest_zone(cur);
	}
	ft_putstr_fd("Total : ", 1);
	ptf_putnbr(total);
	ft_putstr_fd(" bytes\n", 1);
}

void	show_alloc_mem(void)
{
	pthread_mutex_lock(&g_mutex);
	show_alloc_mem_internal();
	pthread_mutex_unlock(&g_mutex);
}
