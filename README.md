# ft_malloc

ft_malloc est une réimplémentation de `malloc`, `free`, `realloc` et `calloc` en C, sous forme de bibliothèque dynamique.
Objectif: gérer soi-même la mémoire du programme en ne passant que par `mmap` et `munmap`, en limitant au maximum les appels système.

## Arborescence

Une fonction publique par fichier, et les outils internes sont rangés par thème.
`myMalloc.h` est le point d'entrée unique: structures, macros et prototypes.


	├── Makefile
	├── myMalloc.h
	├── global.c
	├── myMalloc.c
	├── myFree.c
	├── myRealloc.c
	├── myCalloc.c
	├── myShowAlloc.c
	├── zone.c
	├── block.c
	├── utils.c
	└── libft/

## Fonctionnement

### Les zones
La mémoire est demandée au système par grosses zones avec `mmap`, puis découpée en blocs.
Il y a trois types de zones, selon la taille demandée:

| Type  | Taille d'un bloc   | Taille de la zone                 |
|-------|--------------------|-----------------------------------|
| TINY  | 1 à 128 octets     | 4 pages (16 Ko), au moins 100 blocs   |
| SMALL | 129 à 1024 octets  | 26 pages (104 Ko), au moins 100 blocs |
| LARGE | plus de 1024 octets | une zone par allocation          |

Les zones d'un même type sont dans une liste doublement chaînée, triée par adresse.

### Les blocs
Chaque zone commence par un en-tête `t_zone` (32 octets), suivi de blocs collés les uns aux autres.
Chaque bloc commence par un en-tête `t_block` (32 octets), suivi des données de l'utilisateur.
Tous les pointeurs renvoyés sont alignés sur 16 octets.

	[ t_zone | t_block | données | t_block | données | ... ]

### malloc
Cherche le premier bloc libre assez grand (first fit) dans les zones du bon type.
Si le bloc est trop grand, il est coupé en deux et le reste devient un nouveau bloc libre.
Si aucun bloc ne convient, une nouvelle zone est créée.

### free
Marque le bloc comme libre, puis le fusionne avec ses voisins s'ils sont libres aussi.
Une zone LARGE est rendue au système tout de suite.
Une zone TINY ou SMALL vide est rendue au système, sauf si c'est la dernière de son type (elle est gardée pour les prochains malloc).
Les pointeurs invalides et les doubles free sont ignorés sans planter.

### realloc
Si la nouvelle taille tient dans le bloc actuel et reste du même type, le bloc est gardé sur place.
Sinon, un nouveau bloc est alloué, le contenu est copié, et l'ancien est libéré.

### calloc
Fait un malloc puis met toute la mémoire à zéro, avec une vérification de dépassement sur `nmemb * size`.

### show_alloc_mem
Affiche toutes les zones par adresse croissante, avec chaque bloc utilisé et sa taille.
Exemple de sortie (format du sujet):

	TINY : 0xA0000
	0xA0020 - 0xA004A : 42 bytes
	0xA006A - 0xA00BE : 84 bytes
	SMALL : 0xAD000
	0xAD020 - 0xADEAD : 3725 bytes
	LARGE : 0xB0000
	0xB0020 - 0xBBEEF : 48847 bytes
	Total : 52698 bytes

### Threads
Toutes les fonctions publiques sont protégées par un mutex global.
Elles appellent des versions `_internal` qui ne reprennent jamais le mutex, pour éviter de se bloquer soi-même.

## Compilation

Construire la bibliothèque:

	make

Cela crée `libft_malloc_$HOSTTYPE.so` et le lien symbolique `libft_malloc.so`.

Nettoyer les objets:

	make clean

Nettoyer objets + bibliothèque:

	make fclean

Rebuild complet:

	make re

## Utilisation

Lier un programme directement à la bibliothèque:

	cc main.c -L. -lft_malloc -o prog
	LD_LIBRARY_PATH=. ./prog

Remplacer le malloc de n'importe quel programme existant:

	LD_PRELOAD=./libft_malloc.so ls -la

Pour voir l'état de la mémoire depuis un programme, déclarer puis appeler:

	void	show_alloc_mem(void);

## Tests

Compiler un programme de test avec la bibliothèque (et la libft si besoin):

	cc main.c -I libft libft/libft.a -L. -lft_malloc -pthread -o tester
	LD_LIBRARY_PATH=. ./tester

Points à vérifier: allocations simples, alignement, réutilisation après free, realloc, calloc, pointeurs invalides, tailles trop grandes, show_alloc_mem, stress et threads.

Voir les appels système faits par l'allocateur:

	LD_LIBRARY_PATH=. strace -e trace=mmap,munmap ./tester

## Notes

- Seuls `mmap`, `munmap`, `sysconf` (ou `getpagesize` sous macOS) et les fonctions de la libft sont utilisés.
- `malloc(0)` renvoie un petit bloc valide, qui peut être passé à free.
- Valgrind ne peut pas tester cet allocateur: il remplace lui-même malloc au lancement du programme, donc c'est le sien qui tourne.
- AddressSanitizer est incompatible pour la même raison.
