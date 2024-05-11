/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: kwchu <kwchu@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/04/28 14:12:07 by kwchu         #+#    #+#                 */
/*   Updated: 2024/05/11 14:23:07 by kwchu         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "defines.h"
#include "terminalMode.h"
#include <unistd.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include "moves.h"

void	displayPieceSet(char piece, int highlight, int moves, int lastMove) {
	if (lastMove)
		printf(GREEN);
	else if (moves)
		printf(YELLOW);
	else if (islower(piece))
		printf(WHITE);
	if (highlight)
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
		else if (highlight)
			printf(HIGHLIGHT);
		else
			printf(FILL);
	}
	printf(RESET);
}

int	isHighlightedMove(t_moves *moves, int row, int col) {
	while (moves) {
		if (moves->target[0] == row && moves->target[1] == col)
			return 1;
		moves = moves->next;
	}
	return 0;
}

void	displayBoard(const char board[BOARD_H][BOARD_W], t_display *highlight) {
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

int	convertCoordinateToIndex(char coordinate) {
	if (strchr("abcdefgh", coordinate))
		return coordinate - 'a' + 1;
	else if (strchr("12345678", coordinate))
		return coordinate - '0' - 1;
	return -1;
}

void	putPiece(char board[BOARD_H][BOARD_W], const char piece, const char coordinate[2]) {
	int	index[2];

	index[0] = convertCoordinateToIndex(coordinate[0]);
	index[1] = convertCoordinateToIndex(coordinate[1]);
	if (index[0] == -1 || index[1] == -1)
		return ;
	board[index[0]][index[1]] = piece;
}

void	loadFEN(char board[BOARD_H][BOARD_W], const char *FEN) {
	int	index[2] = {0, 0};

	for (size_t i = 0; FEN[i] && FEN[i] != ' '; i++) {
		if (FEN[i] == '/') {
			index[0]++;
			continue ;
		}
		if (isdigit(FEN[i])) {
			index[1] += FEN[i] - '0';
			if (index[1] == 8)
				index[1] = 0;
			continue ;
		}
		board[index[0]][index[1]] = FEN[i];
		index[1]++;
		if (index[1] == 8)
			index[1] = 0;
	}
}

void	initBoard(char board[BOARD_H][BOARD_W]) {
	printf(SAVE_CURSOR_POS);
	for (size_t i = 0; i < BOARD_H; i++) {
		for (size_t j = 0; j < BOARD_W; j++) {
			board[i][j] = '.';
		}
	}
}

void	handleArrowKey(char c, t_display *highlight) {
	if (read(STDIN_FILENO, &c, 1) && c == '[') {
		read(STDIN_FILENO, &c, 1);
		if (c == 'A')
			highlight->cursor[0] - 1 >= 0 ? highlight->cursor[0]-- : 0;
		else if (c == 'B')
			highlight->cursor[0] + 1 < BOARD_H ? highlight->cursor[0]++ : BOARD_H;
		else if (c == 'C')
			highlight->cursor[1] + 1 < BOARD_W ? highlight->cursor[1]++ : BOARD_H;
		else if (c == 'D')
			highlight->cursor[1] - 1 >= 0 ? highlight->cursor[1]-- : 0;
	}
}

void	deselectPiece(t_display *highlight) {
	highlight->selectedPiece[0] = -1;
	cleanupMoves(&highlight->moves);
}

void	selectPiece(t_display *highlight) {
	highlight->selectedPiece[0] = highlight->cursor[0];
	highlight->selectedPiece[1] = highlight->cursor[1];
}

void	movePieceToTarget(char board[BOARD_H][BOARD_W], int self[2], int target[2]) {
	board[target[0]][target[1]] = board[self[0]][self[1]];
	board[self[0]][self[1]] = '.';
}

void	updateLastMove(t_display *highlight, int self[2], int target[2]) {
	highlight->lastMove[0][0] = self[0];
	highlight->lastMove[0][1] = self[1];
	highlight->lastMove[1][0] = target[0];
	highlight->lastMove[1][1] = target[1];
}

void	extraMoveEnPassant(char board[BOARD_H][BOARD_W], int row, int col) {
	board[row][col] = '.';
}

// void	extraMoveCastling(char board[BOARD_H][BOARD_W], int self[2], int target[2]) {
	
// }

void	applySpecialMoveType(char board[BOARD_H][BOARD_W], t_moves *moves, int target[2]) {
	while (moves) {
		if (moves->target[0] == target[0] && moves->target[1] == target[1])
			break ;
		moves = moves->next;
	}
	if (moves == NULL)
		return ;
	if (abs(moves->specialMove) == 1)
		extraMoveEnPassant(board, target[0] + moves->specialMove, target[1]);
	else if (abs(moves->specialMove) == 2)
		return ;
}

void	makeMove(char board[BOARD_H][BOARD_W], t_display *highlight) {
	movePieceToTarget(board, highlight->selectedPiece, highlight->cursor);
	applySpecialMoveType(board, highlight->moves, highlight->cursor);
	updateLastMove(highlight, highlight->selectedPiece, highlight->cursor);
}

void	handleSelection(char board[BOARD_H][BOARD_W], t_display *highlight) {
	if (highlight->cursor[0] == highlight->selectedPiece[0] && \
		highlight->cursor[1] == highlight->selectedPiece[1])
		deselectPiece(highlight);
	else if (isHighlightedMove(highlight->moves, highlight->cursor[0], highlight->cursor[1])) {
		makeMove(board, highlight);
		deselectPiece(highlight);
	}
	else if (board[highlight->cursor[0]][highlight->cursor[1]] == '.')
		deselectPiece(highlight);
	else {
		deselectPiece(highlight);
		selectPiece(highlight);
		getMovesAtSquare(&highlight->moves, board, highlight->selectedPiece, highlight->lastMove);
	}
}

void	initHighlight(t_display *highlight) {
	highlight->cursor[0] = 0;
	highlight->cursor[1] = 0;
	highlight->selectedPiece[0] = -1;
	highlight->selectedPiece[1] = 0;
	highlight->lastMove[0][0] = -1;
	highlight->lastMove[0][1] = 0;
	highlight->lastMove[1][0] = 0;
	highlight->lastMove[1][1] = 0;
	highlight->moves = NULL;
}

int	main(void) {
	char			board[BOARD_H][BOARD_W];
	struct termios	original;
	char			c;
	t_display		highlight;

	initBoard(board);
	initHighlight(&highlight);
	loadFEN(board, "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR");
	displayBoard(board, &highlight);
	enableRawMode(&original);
	while (read(STDIN_FILENO, &c, 1) && c != 'q') {
		if (c == ' ')
			handleSelection(board, &highlight);
		else if (c == '\033')
			handleArrowKey(c, &highlight);
		displayBoard(board, &highlight);
	}
	cleanupMoves(&highlight.moves);
	disableRawMode(&original);
	return 0;
}
