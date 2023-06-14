##
## EPITECH PROJECT, 2023
## Zappy
## File description:
## Makefile
##

NAME    =   zappy_ai

all: ${NAME}

${NAME}:
	cp src/main.py ${NAME}
	chmod a+x ${NAME}

clean:
	${RM} -r build/
	${RM} -r src/__pycache__/
	${RM} -r tests/__pycache__/

fclean: clean
	${RM} ${NAME}

re:		fclean all

.PHONY: all clean fclean re
