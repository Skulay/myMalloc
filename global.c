#include "myMalloc.h"

t_heap	g_heap = {NULL, NULL, NULL};
pthread_mutex_t	g_mutex = PTHREAD_MUTEX_INITIALIZER;