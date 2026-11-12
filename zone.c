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

}

t_zone	*create_zone(int type, size_t size)
{

}