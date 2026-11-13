#ifndef MYMALLOC_H
# define MYMALLOC_H

# include "libft.h"
# include <stdlib.h>
# include <unistd.h>
# include <sys/mman.h>
# include <pthread.h>
# include <stdint.h>

# define TINY_MAX		128
# define SMALL_MAX		1024

# define MIN_ALLOCS		100

# define TYPE_TINY		0
# define TYPE_SMALL		1
# define TYPE_LARGE		2

# define ALIGNMENT		16
# define ALIGN(size)	(((size) + ALIGNMENT - 1) & ~(ALIGNMENT - 1))

# define ZONE_HDR		sizeof(t_zone) // taille header zone
# define BLOCK_HDR		sizeof(t_block) // taille header block

# define FIRST_BLOCK(z)	((t_block *)((t_zone *)(z) + 1)) // saute l'header de zone | +1 = 32octet
# define NEXT_BLOCK(b)	((t_block *)((char *)BLOCK_DATA(b) + (b)->size)) // pas besoin de next t_block reste a 32 octet
# define BLOCK_DATA(b)	((void *)((t_block *)(b) + 1)) // saute l'header de block

# define ZONE_END(z)	((char *)(z) + (z)->size) // adresse du premier octet qui n'appatiens plus a la zone en question 
# define MIN_SPLIT		(BLOCK_HDR + ALIGNMENT) // pour l plus petit block possible 32octet (header) + 16octet (plus petite taille alligner)

typedef struct s_block
{
	struct s_block	*prev;
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
}	t_heap;

_Static_assert(sizeof(t_block) % ALIGNMENT == 0, "t_block must be a multiple of 16");
_Static_assert(sizeof(t_zone) % ALIGNMENT == 0, "t_zone must be a multiple of 16");

extern t_heap			g_heap;    // allocations
extern pthread_mutex_t	g_mutex;   // thread-safety

// fonction pour le thread safety
void	free(void *ptr);
void	*malloc(size_t size);
void	*realloc(void *ptr, size_t size);
void	show_alloc_mem(void);
void	*calloc(size_t nmemb, size_t size);

// fonction classique
void	*malloc_internal(size_t size);
void	free_internal(void *ptr);
void	*realloc_internal(void *ptr, size_t size);
void	show_alloc_mem_internal(void);
void	*calloc_internal(size_t nmemb, size_t size);

//utils
size_t	page_size(void);
size_t	round_to_page(size_t n);
size_t	zone_size(size_t max_alloc);
int		get_type(size_t size);
t_zone	**get_list(int type);

// zone
void	insert_zone(t_zone **list, t_zone *zone);
void	remove_zone(t_zone **list, t_zone *zone);
t_zone	*create_zone(int type, size_t size);

// block
t_block	*find_free_block(t_zone *zone, size_t aligned, t_zone **out);
void	split_block(t_zone *zone, t_block *block, size_t aligned);
t_block	*find_block(void *ptr, t_zone **out);
void	merge_with_next(t_zone *zone, t_block *block);

#endif