##
## EPITECH PROJECT, 2023
## Zappy
## File description:
## Makefile
##

NAME    =   zappy_ai

all: ${NAME}

${NAME}:
	cp src/main.py ../${NAME}
	chmod +x ../${NAME}

clean:
	${RM} src/__pycache__/
	${RM} ./sources/__pycache__/
	${RM} ./tests/__pycache__/
	${RM} ./build/
	${RM} ./dist/

fclean: clean
	${RM} ../${NAME}

re:		fclean all

.PHONY: all clean fclean re
