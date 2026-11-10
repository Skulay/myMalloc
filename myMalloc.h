#ifndef MYMALLOC_H
# define MYMALLOC_H

# include <stdlib.h>
# include <unistd.h>
# include <sys/mman.h>
# include <pthread.h>

# define TINY_MAX		128
# define SMALL_MAX		1024

# define TINY_PAGES		4
# define SMALL_PAGES	26

# define TYPE_TINY		0
# define TYPE_SMALL		1
# define TYPE_LARGE		2

# define ALIGNMENT		16
# define ALIGN(size)	(((size) + ALIGNMENT - 1) & ~(ALIGNMENT - 1))

typedef struct s_block
{
	struct s_block	*next;
	size_t			size;
	size_t			user_size;   // pour show alloc mem
	int				is_free;     // 1 = libre, 0 = occupé
}	t_block;

typedef struct s_zone
{
	struct s_zone	*next;
	struct s_zone	*prev;
	size_t			size;        // taille de la zone (multiple de la page)
	size_t			type;        // macro de type au dessus
}	t_zone;

typedef struct s_heap
{
	t_zone			*tiny;
	t_zone			*small;
	t_zone			*large;
}   t_heap;

_Static_assert(sizeof(t_block) % ALIGNMENT == 0, "t_block must be a multiple of 16");
_Static_assert(sizeof(t_zone) % ALIGNMENT == 0, "t_zone must be a multiple of 16");

extern t_heap			g_heap;    // allocations
extern pthread_mutex_t	g_mutex;   // thread-safety

// fonction pour le thread safety
void	free(void *ptr);
void	*malloc(size_t size);
void	*realloc(void *ptr, size_t size);
void	show_alloc_mem(void);

// fonction classique
void	*malloc_internal(size_t size);
void	free_internal(void *ptr);
void	*realloc_internal(void *ptr, size_t size);
void	show_alloc_mem_internal(void);

#endif