# SPDX-FileCopyrightText: 2020 The at42 Libft Unit Tests Contributors (see CONTRIBUTORS.md)
#
# SPDX-License-Identifier: GPL-3.0-or-later

TEST_BIN = test.bin

TEST_SRC_PATH = libft_test
TEST_SRC_BASENAME = $(patsubst $(TEST_SRC_PATH)/%,%,$(wildcard $(TEST_SRC_PATH)/*.c))

LIBFT_SRC_PATH = libft
LIBFT_SRC = $(wildcard $(LIBFT_SRC_PATH)/*.c)
LIBFT_SRC_BASENAME = $(patsubst $(LIBFT_SRC_PATH)/%,%,$(LIBFT_SRC))

COMMON_SRC = $(filter $(LIBFT_SRC_BASENAME),$(TEST_SRC_BASENAME))

TEST_SRC = $(COMMON_SRC:%=$(TEST_SRC_PATH)/%)
TEST_SRC += $(wildcard $(TEST_SRC_PATH)/rand/*.c)
TEST_SRC += $(wildcard $(TEST_SRC_PATH)/utils/*.c)
TEST_OBJ = $(TEST_SRC:.c=.o)
TEST_CC = gcc
TEST_CFLAGS = -Wall -Wextra -g -fsanitize=address,undefined

LIBFT_OBJ = $(LIBFT_SRC:.c=.o)
LIBFT_CC = clang
LIBFT_CFLAGS = $(TEST_CFLAGS) -Werror

# Inspired by Auto Dependency Generation (by Paul D. Smith)
# see http://make.mad-scientist.net/papers/advanced-auto-dependency-generation/#advanced
DEP_FILES = $(TEST_SRC:%.c=%.d) $(LIBFT_SRC:%.c=%.d)
DEP_FLAGS = -MT $@ -MMD -MP -MF $*.Td
POSTCOMPILE = mv -f $*.Td $*.d && touch $@

LIB = criterion # our testing framework
LIB += dl # dynamicaly load libraries functions to bypass mock in tests
LIB += bsd # <bsd/strings.h> : strlcat for linux
LIBS = $(LIB:%=-l%)

MIMICK = /usr/lib/libmimick.a

RM = rm -rf
GREP = grep
NORM = .norminette/norminette.rb
AR = ar rcs

NORM_TMP_FILE = /dev/shm/at42.norm.txt


all: norm $(TEST_BIN)

$(TEST_BIN): $(TEST_OBJ) $(LIBFT_OBJ) $(MIMICK)
	$(CC) $(TEST_CFLAGS) $(LIBS) -o $@ $^

%.o: %.c

$(TEST_OBJ): %.o: %.c %.d Makefile
	$(TEST_CC) $(TEST_CFLAGS) $(DEP_FLAGS) $(INCLUDE) -c -o $@ $<
	$(POSTCOMPILE)

$(LIBFT_OBJ): %.o: %.c %.d Makefile
	$(LIBFT_CC) $(LIBFT_CFLAGS) $(DEP_FLAGS) $(INCLUDE) -c -o $@ $<
	$(POSTCOMPILE)

clean:
	$(RM) $(TEST_OBJ) $(SRC_OBJ)
	$(RM) $(DEP_FILES)
	$(RM) $(DEP_FILES:%.d=%.Td)

tclean:
	$(RM) $(TEST_BIN)

fclean: clean tclean

re: fclean all

test: all
	./$(TEST_BIN)

norm:
	$(NORM) $(LIBFT_SRC) $(LIBFT_SRC_PATH)/libft.h | tee $(NORM_TMP_FILE)
	@echo
	@! $(GREP) "^Error\|^Warning" $(NORM_TMP_FILE) --color -B 1
	@$(RM) $(NORM_TMP_FILE)

.PHONY: all clean tclean fclean re test norm

$(DEP_FILES):

-include $(DEP_FILES)
