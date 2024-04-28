NAME = terminalchess

CFLAGS = -Wall -Wextra -Werror

LINKS = -lreadline

INCLUDES = -I./include

SRC = main.c board.c pawnMove.c drawPiece.c coordToIndex.c executeMove.c

DIR_SRC = src
SRC := ${addprefix ${DIR_SRC}/, ${SRC}}

DIR_OBJ = obj
OBJ = ${subst ${DIR_SRC}/, ${DIR_OBJ}/, ${SRC:.c=.o}}


${NAME}: ${OBJ}
	cc ${CFLAGS} $^ ${LINKS} -o $@

all: ${NAME}

${OBJ}: ${DIR_OBJ}/%.o: ${DIR_SRC}/%.c
	@mkdir -p ${@D}
	cc ${CFLAGS} ${INCLUDES} -c $< -o $@

debug: CFLAGS += -g
debug: re

clean:
	rm -f ${OBJ}

fclean: clean
	rm -f ${NAME}

re: fclean all

.PHONY: all clean fclean re debug