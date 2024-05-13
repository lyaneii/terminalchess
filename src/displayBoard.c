/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   displayBoard.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: kwchu <kwchu@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/12 17:38:59 by kwchu         #+#    #+#                 */
/*   Updated: 2024/05/13 13:40:52 by kwchu         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <ctype.h>
#include "moves.h"
#include "controls.h"

static void	displayPieceSet(char piece, int cursor, int moves, int lastMove) {
	if (lastMove)
		printf(GREEN);
	else if (moves)
		printf(YELLOW);
	else if (islower(piece))
		printf(WHITE);
	if (cursor)
		printf(RED);
	piece = tolower(piece);
	if (piece == 'p')
		printf("♟︎");
	else if (piece == 'r')
		printf("♜");
	else if (piece == 'n')
		printf("♞");
	else if (piece == 'b')
		printf("♝");
	else if (piece == 'k')
		printf("♚");
	else if (piece == 'q')
		printf("♛");
	else if (piece == '.') {
		if (lastMove)
			printf(LAST_MOVE);
		else if (moves)
			printf(MOVES);
		else if (cursor)
			printf(HIGHLIGHT);
		else
			printf(FILL);
	}
	printf(RESET);
}

void	displayBoard(const char board[BOARD_H][BOARD_W], t_boardInfo *highlight) {
	printf(LOAD_CURSOR_POS);
	for (int i = 0; i < BOARD_H; i++) {
		for (int j = 0; j < BOARD_W; j++) {
			if (i == highlight->cursor[0] && j == highlight->cursor[1])
				displayPieceSet(board[i][j], 1, 0, 0);
			else if (highlight->selectedPiece[0] != -1 && \
					i == highlight->selectedPiece[0] && j == highlight->selectedPiece[1])
				displayPieceSet(board[i][j], 0, 1, 0);
			else if (isHighlightedMove(highlight->moves, i, j))
				displayPieceSet(board[i][j], 0, 1, 0);
			else if (highlight->lastMove[0][0] != -1 && \
					i == highlight->lastMove[0][0] && j == highlight->lastMove[0][1])
				displayPieceSet(board[i][j], 0, 0, 1);
			else if (highlight->lastMove[0][0] != -1 && \
					i == highlight->lastMove[1][0] && j == highlight->lastMove[1][1])
				displayPieceSet(board[i][j], 0, 0, 1);
			else
				displayPieceSet(board[i][j], 0, 0, 0);
			printf(" ");
		}
		printf("\n");
	}
	printf("[q = quit]\n");
}