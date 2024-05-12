NAME = terminalchess

CFLAGS = -Wall -Wextra -Werror

LINKS = 

INCLUDES = -I./include

SRC =	main.c terminalMode.c pawnMove.c bishopMove.c getMoves.c initialise.c \
		kingMove.c knightMove.c queenMove.c rookMove.c possibleMoves.c movesList.c \
		piecesAttackingSquare.c scanChecks.c controls.c displayBoard.c specialMoves.c

DIR_SRC = src
SRC := ${addprefix ${DIR_SRC}/, ${SRC}}

DIR_OBJ = obj
OBJ = ${subst ${DIR_SRC}/, ${DIR_OBJ}/, ${SRC:.c=.o}}

DIR_HEADERS = include
HEADERS = defines.h controls.h displayBoard.h initialise.h moves.h terminalMode.h
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