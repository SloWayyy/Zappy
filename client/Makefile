##
## EPITECH PROJECT, 2023
## Zappy
## File description:
## Makefile
##

CMAKE_FLAGS		=	-G "Unix Makefiles"

NAME			=	zappy_gui

DIR_DEST		=	libs/

SDK_COMM		=	communication_sdk.so
SDK_COMM_PATH	=	../sdk/communication

all: sdk $(NAME)

sdk: $(NAME_SDK)
	rm -rf $(DIR_DEST)
	$(MAKE) -C $(SDK_COMM_PATH)
	mkdir -p $(DIR_DEST)
	cp -r $(SDK_COMM_PATH)/include/ $(SDK_COMM_PATH)/$(SDK_COMM) $(DIR_DEST)

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
