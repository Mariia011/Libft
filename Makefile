NAME = libft.a
CC = cc
CFLAGS = -Wall -Wextra -Werror
SRC = ./src/
EXEC = a.out
ROOT = ./

FILES = $(wildcard $(ROOT)*.c)
# OBJS = $(FILES:.c=.o)
OBJS = $(ROOT)*.o

.PHONY:  all clean fclean re

all: $(NAME)

$(NAME) : $(OBJS)
	ar -rcs $(NAME) $(OBJS)

$(OBJS) : $(FILES)
	$(CC) $(CFLAGS) -c $(FILES)


clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME) $(EXEC)

re: fclean all
