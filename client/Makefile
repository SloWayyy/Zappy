##
## EPITECH PROJECT, 2023
## Zappy
## File description:
## Makefile
##

CMAKE_FLAGS		=	-G "Unix Makefiles"

NAME			=	zappy_gui

all: $(NAME)

build:
	mkdir -p build

build/Makefile: build
	cd build && cmake $(CMAKE_FLAGS) ..

build/$(NAME): build/Makefile
	$(MAKE) -C build/

$(NAME): build/$(NAME)
	cp build/$(NAME) .

clean: build/Makefile
	$(MAKE) -C build/ clean

fclean: clean
	$(RM) $(NAME)

re:
	$(MAKE) fclean
	$(MAKE) all

.PHONY: all clean fclean re
