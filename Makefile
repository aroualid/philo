CC = cc
CFLAGS=  -Wall -Wextra -Werror  -g3
SRCS = main.c
OBJS = $(SRCS:%.c=%.o)
NAME = philo

.PHONY: all clean fclean re bonus

all:  $(NAME) 

$(NAME): $(OBJS) 
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) 

clean:
	$(RM) $(OBJS)
fclean: clean
	$(RM) $(NAME)
re: fclean all


