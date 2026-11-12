ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

NAME    = libft_malloc_$(HOSTTYPE).so
LINK    = libft_malloc.so

CC      = cc
CFLAGS  = -Wall -Wextra -Werror -fPIC
INC     = -I . -I libft

LIBFT   = libft/libft.a

OBJ_DIR = obj

SRC     = myMalloc.c \
          myFree.c \
          myRealloc.c \
          myShowAlloc.c \
		  global.c \
		  zone.c \
          utils.c

OBJ     = $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))

all: $(LINK)

$(LINK): $(NAME)
	ln -sf $(NAME) $(LINK)

$(NAME): $(LIBFT) $(OBJ)
	$(CC) -shared $(OBJ) $(LIBFT) -o $(NAME)

$(LIBFT): FORCE
	make -C libft

$(OBJ_DIR)/%.o: %.c myMalloc.h
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)
	make -C libft clean

fclean: clean
	rm -f $(NAME) $(LINK)
	make -C libft fclean

re: fclean all

FORCE:

.PHONY: all clean fclean re FORCE