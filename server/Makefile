##
## EPITECH PROJECT, 2023
## Zappy
## File description:
## Makefile
##

SRC			=	src/core/fdsets.c \
				src/core/init.c \
				src/core/input.c \
				src/core/loop.c \
				src/core/map.c \
				src/core/scheduler.c \
				src/core/tick.c \
				src/graphical/command.c \
				src/graphical/data.c \
				src/graphical/events.c \
				src/graphical/map.c \
				src/graphical/map_size.c \
				src/graphical/player.c \
				src/graphical/time.c \
				src/graphical/team_name.c \
				src/objects/buffers.c \
				src/objects/clients.c \
				src/objects/players.c \
				src/objects/tasks.c \
				src/objects/teams.c \
				src/player/actions.c \
				src/player/command.c \
				src/player/food.c \
				src/player/info.c \
				src/player/join.c \
				src/player/move.c \
				src/util/arguments/args.c \
				src/util/arguments/check.c \
				src/util/arguments/handlers.c \
				src/util/arguments/names.c \
				src/util/arrays.c \
				src/util/buffer_in.c \
				src/util/buffer_out.c \
				src/util/util.c \
				src/server.c

MAIN		=	src/main.c

TESTS		=	tests/test_server.c

INC			=	include/

NAME		=	zappy_server
TEST		=	unit_tests

OBJ			=	$(SRC:.c=.o)
OBJ_M 		=	$(MAIN:.c=.o)
OBJ_T		=	$(TESTS:.c=.o)

CC			=	gcc

CFLAGS		=	-Wall -Wextra -Wpedantic
CPPFLAGS	=	-iquote $(INC)

all: $(NAME)

$(NAME): $(OBJ) $(OBJ_M)
	$(CC) -o $(NAME) $(OBJ) $(OBJ_M)

clean:
	$(RM) $(OBJ)
	$(RM) $(OBJ_M)
	$(RM) $(OBJ_T)
	find -name "*.gcda" -delete -o -name "*.gcno" -delete

debug: CPPFLAGS += -g3
debug: re

fclean:	clean
	$(RM) $(NAME)
	$(RM) $(TEST)

re:	fclean all

tests_run: CFLAGS += --coverage
tests_run: LDLIBS += -lcriterion
tests_run: clean $(OBJ) $(OBJ_T)
	$(CC) -o $(TEST) $(OBJ) $(OBJ_T) $(LDLIBS) --coverage
	$(RM) $(OBJ)
	./$(TEST)

.PHONY: all clean fclean re tests_run
