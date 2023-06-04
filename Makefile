##
## EPITECH PROJECT, 2023
## Zappy
## File description:
## Makefile
##

NAME_AI		=	zappy_ai
NAME_CLIENT	=	zappy_gui
NAME_SERVER	=	zappy_server

$(NAME_AI):
	$(MAKE) -C ai/
	cp ai/$(NAME_AI) .

$(NAME_CLIENT):
	$(MAKE) -C client/
	cp client/$(NAME_CLIENT) .

$(NAME_SERVER):
	$(MAKE) -C server/
	cp server/$(NAME_SERVER) .

ai: $(NAME_AI)

all:
	$(MAKE) $(NAME_AI)
	$(MAKE) $(NAME_CLIENT)
	$(MAKE) $(NAME_SERVER)

ci:
	$(MAKE) $(NAME_AI)
	$(MAKE) $(NAME_SERVER)

client: $(NAME_CLIENT)

clean:
	$(MAKE) -C ai/ clean
	$(MAKE) -C client/ clean
	$(MAKE) -C server/ clean

fclean:	clean
	$(MAKE) -C ai/ fclean
	$(MAKE) -C client/ fclean
	$(MAKE) -C server/ fclean
	$(RM) $(NAME_AI)
	$(RM) $(NAME_CLIENT)
	$(RM) $(NAME_SERVER)

install:
	echo "Installing Zappy dependencies..."
	./install/raylib_install.sh

re:	fclean all

server: $(NAME_SERVER)

.PHONY: ai all ci clean client fclean install server re
