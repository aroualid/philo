NAME = philo
CC = cc
CFLAGS=  -Wall -Wextra -Werror  -g3

SRC_PATH = src/
OBJ_PATH = obj/
SRC_NAME = main.c \
		   utils1.c\
		   my_atol.c\
		   my_usleep.c\
		   eat.c\
		   create_threads.c\
		   one_philo.c

OBJ_NAME = $(SRC_NAME:.c=.o)

OBJ = $(addprefix $(OBJ_PATH), $(OBJ_NAME))
SRC = $(addprefix $(SRC_PATH), $(SRC_NAME))

.DEFAULT_GOAL := all

.PHONY: all clean fclean re 

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ)

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	mkdir -p $(@D)
	$(CC) $(CFLAGS) -o $@ -c $<

-include $(OBJ:%.o=%.d)

all: $(NAME)

clean:
	rm -rf $(OBJ_PATH)

fclean: clean
	rm -rf $(NAME)

re:
	$(MAKE) fclean all

