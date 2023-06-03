##
## EPITECH PROJECT, 2023
## Zappy
## File description:
## Makefile
##

NAME_AI		=	zappy_ai
NAME_CLIENT	=	zappy_gui
NAME_SERVER	=	zappy_server

all: $(NAME_AI) $(NAME_CLIENT) $(NAME_SERVER)

$(NAME_AI):

$(NAME_CLIENT):
	$(MAKE) -C client/
	cp client/$(NAME_CLIENT) .

$(NAME_SERVER):
	$(MAKE) -C server/
	cp server/$(NAME_SERVER) .

clean:
	$(MAKE) -C client/ clean
	$(MAKE) -C server/ clean

fclean:	clean
	$(MAKE) -C client/ fclean
	$(MAKE) -C server/ fclean
	$(RM) $(NAME_AI)
	$(RM) $(NAME_CLIENT)
	$(RM) $(NAME_SERVER)

install:
	echo "Installing Zappy dependencies..."
	./install/raylib_install.sh

re:	fclean all

.PHONY: all clean fclean install re
