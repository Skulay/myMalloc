#include "myMalloc.h"

void    show_alloc_mem_internal(void)
{

}

void    show_alloc_mem(void)
{
	pthread_mutex_lock(&g_mutex);
	show_alloc_mem_internal(void);
	pthread_mutex_unlock(&g_mutex);
}