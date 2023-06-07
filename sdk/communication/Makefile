##
## EPITECH PROJECT, 2023
## Zappy
## File description:
## Makefile
##

SRC			=	src/ACommunicationModule.cpp \
				src/ModuleUtils.cpp \
				src/ZappyCommunicationModule.cpp

TESTS		=	tests/TestSdk.cpp

OBJ			=	$(SRC:.cpp=.o)
OBJ_T		=	$(TESTS:.cpp=.o)

NAME		=	communication_sdk.so
TEST		=	unit_tests

CXX			=	g++
CXXFLAGS	=	-Wall -Wextra -Wpedantic
CPPFLAGS	=	-iquote include/

DIR_DEST	=	../../client/sdk

all:	$(NAME)

$(NAME): CXXFLAGS += -fPIC
$(NAME): $(OBJ)
	g++ $(CXXFLAGS) -o $(NAME) $(OBJ) --shared

clean:
	$(RM) $(OBJ)
	$(RM) $(OBJ_T)
	find . -name "*.gcda" -delete -o -name "*.gcno" -delete

debug: CXXFLAGS += -g3
debug: re

fclean:	clean
	rm -f $(NAME)
	rm -f $(OBJ)
	rm -rf ../../client/sdk

re:	fclean all

tests_run: CXXFLAGS += --coverage
tests_run: CPPFLAGS += -iquote src/
tests_run: LDLIBS += -lcriterion
tests_run: clean $(OBJ) $(OBJ_T)
	$(CXX) -o $(TEST) $(OBJ) $(OBJ_T) $(LDLIBS) --coverage
	$(RM) $(OBJ)
	./$(TEST)

.PHONY:	all clean debug fclean re tests_run
