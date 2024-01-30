NAME = libft.a
CC = cc
CFLAGS = -Wall -Wextra -Werror
SRC = ./src/
EXEC = a.out
ROOT = ./

GITCLONE = git clone
TRIPOULLE = git@github.com:Tripouille/libftTester.git
WARMACHINE = git@github.com:0x050f/libft-war-machine.git
UNIT-TEST = git@github.com:alelievr/libft-unit-test.git

FILES = $(wildcard $(ROOT)*.c)
# OBJS = $(FILES:.c=.o)
OBJS = $(ROOT)*.o

.PHONY:  all clean fclean re get_testers delete_testers update_testers

all: $(NAME)

$(NAME) : $(OBJS)
	ar -rcs $(NAME) $(OBJS)

$(OBJS) : $(FILES)
	$(CC) $(CFLAGS) -c $(FILES)


get_testers :
	$(GITCLONE) $(TRIPOULLE) tripoulle_test
	$(GITCLONE) $(WARMACHINE) war-machine
	$(GITCLONE) $(UNIT-TEST) ../unit-test

delete_testers :
	rm -rf ./tripoulle_test ./war-machine ../unit-test

update_testers : delete_testers get_testers


clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME) $(EXEC)

re: fclean all
