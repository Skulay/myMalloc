# Libft

Libft est une bibliothèque C qui regroupe des utilitaires réutilisables pour les projets 42 et hors 42.
Objectif: fournir une base stable, facile à intégrer, et organisée par modules.

## Arborescence

Les sources sont rangées dans `src/` par modules.
`libft.h` est à la racine et sert de point d’entrée unique.


	├── Makefile
	├── libft.h
	└── src/
		├── ctype/
		├── string/
		├── memory/
		├── convert/
		├── print/
		└── list/

## Dossiers

### ctype/
Classification et transformation de caractères.
But: tester des caractères (lettre, chiffre, ASCII, imprimable) et gérer les conversions de casse.

### string/
Manipulation de chaînes C (char *).
But: mesurer, copier, concaténer, chercher, découper, et transformer des chaînes.

### memory/
Outils bas niveau sur la mémoire brute (void *).
But: initialiser, copier, déplacer, comparer, et rechercher dans des blocs mémoire.

### convert/
Conversion entre texte et types numériques.
But: parser des nombres depuis des chaînes et produire des chaînes depuis des valeurs numériques.

### print/
Regroupe les fonctions liées à l’affichage et à l’I/O.
- sorties sur file descriptor (stdout, stderr, fichiers)
- ft_printf
- get_next_line (bonus si présent)

But: centraliser tout ce qui touche aux entrées/sorties.

### list/
Listes chaînées (bonus).
But: créer, parcourir, ajouter, supprimer, et transformer des listes de façon sûre.

## Compilation

Construire la bibliothèque:

	make

Nettoyer les objets:

	make clean

Nettoyer objets + bibliothèque:

	make fclean

Rebuild complet:

	make re

## Utilisation dans un projet

Exemple simple si libft.a et libft.h sont au même niveau que ton main.c:
	cc -Wall -Wextra -Werror main.c -L. -lft

Si libft est dans un dossier libft/:
		cc -Wall -Wextra -Werror main.c -Llibft -lft -Ilibft

## Notes

- libft.h est le point d’entrée unique: il expose l’API publique.
- L’organisation par dossiers suit une logique “module” pour simplifier maintenance et debug.
- print/ centralise printf et gnl pour éviter la dispersion des fichiers I/O.
