#include "myMalloc.h"

// -> insert_zone | mettre la zone dans la list
// -> remove_zone | enlever la zone de la liste
// -> create_zone | creer une nouvelle zone
// -> ?? 		  | en fonction des besoin  



void	insert_zone(t_zone **list, t_zone *zone)
{
	t_zone *prev;
	t_zone *cur;

	prev = NULL;
	cur = *list;
	while (cur && cur < zone)
	{
		prev = cur;
		cur = cur->next;
	}
	zone->prev = prev;
	zone->next = cur;
	if (cur)
		cur->prev = zone;
	if (prev)
		prev->next = zone;
	else
		*list = zone;
}

void	remove_zone(t_zone **list, t_zone *zone)
{
	if (zone->prev)
		zone->prev->next = zone->next;
	else
		*list = zone->next;
	if (zone->next)
		zone->next->prev = zone->prev;
	munmap(zone, zone->size);
}

t_zone	*create_zone(int type, size_t size)
{
	t_zone	*zone;
	t_block *first;

	// NULL = adresse auto | lecture+écriture | privée, sans fichier, remplie de 0 | fd -1, offset 0 | erreur = MAP_FAILED
	zone = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
	if (zone == MAP_FAILED)
		return (NULL);
	zone->size = size;
	zone->type = type;
	first = FIRST_BLOCK(zone);
	first->prev = NULL;
	first->size = size - ZONE_HDR - BLOCK_HDR;
	first->user_size = 0;
	first->is_free = 1;
	insert_zone(get_list(type), zone);
	return (zone);
}