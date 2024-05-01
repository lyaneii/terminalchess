NAME = terminalchess

CFLAGS = -Wall -Wextra -Werror

LINKS = 

INCLUDES = -I./include

SRC =	main.c board.c pawnMove.c drawPiece.c coordToIndex.c \
		executeMove.c knightMove.c moveList.c bishopMove.c \
		pieceCount.c

DIR_SRC = src
SRC := ${addprefix ${DIR_SRC}/, ${SRC}}

DIR_OBJ = obj
OBJ = ${subst ${DIR_SRC}/, ${DIR_OBJ}/, ${SRC:.c=.o}}

DIR_HEADERS = include
HEADERS = board.h colours.h move.h piece.h
HEADERS := ${addprefix ${DIR_HEADERS}/, ${HEADERS}}

${NAME}: ${OBJ}
	cc ${CFLAGS} $^ ${LINKS} -o $@

all: ${NAME}

${OBJ}: ${DIR_OBJ}/%.o: ${DIR_SRC}/%.c ${HEADERS}
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