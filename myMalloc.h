#ifndef MYMALLOC_H
#define MYMALLOC_H

#include <stdlib.h>

#define TINY		128
#define TINY_PAGES	4
#define SMALL		1024
#define SMALL_PAGES	26

void	free(void *ptr);
void	*malloc(size_t size);
void	*realloc(void *ptr, size_t size);

#endif