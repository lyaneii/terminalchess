/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: kwchu <kwchu@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/04/28 14:12:07 by kwchu         #+#    #+#                 */
/*   Updated: 2024/05/12 17:29:27 by kwchu         ########   odam.nl         */
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
#include "initialise.h"

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



void	handleArrowKey(char c, t_boardInfo *highlight) {
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

void	deselectPiece(t_boardInfo *highlight) {
	highlight->selectedPiece[0] = -1;
	cleanupMoves(&highlight->moves);
}

void	selectPiece(t_boardInfo *highlight) {
	highlight->selectedPiece[0] = highlight->cursor[0];
	highlight->selectedPiece[1] = highlight->cursor[1];
}

void	movePieceToTarget(char board[BOARD_H][BOARD_W], int self[2], int target[2]) {
	board[target[0]][target[1]] = board[self[0]][self[1]];
	board[self[0]][self[1]] = '.';
}

void	updateLastMove(t_boardInfo *highlight, int self[2], int target[2]) {
	highlight->lastMove[0][0] = self[0];
	highlight->lastMove[0][1] = self[1];
	highlight->lastMove[1][0] = target[0];
	highlight->lastMove[1][1] = target[1];
}

void	extraMoveEnPassant(char board[BOARD_H][BOARD_W], int row, int col) {
	board[row][col] = '.';
}

void	extraMoveCastling(char board[BOARD_H][BOARD_W], int target[2], int castleRights[2][2]) {
	int		castleSide = target[1] == 2 ? 0 : 1;
	int		rookOffset = target[1] == 2 ? 1 : -1;
	int 	rookCastlePos[2] = {0, 7};

	board[target[0]][target[1] + rookOffset] = board[target[0]][rookCastlePos[castleSide]];
	board[target[0]][rookCastlePos[castleSide]] = '.';
	if (board[target[0]][target[1] + rookOffset] == 'r') {
		castleRights[1][0] = 0;
		castleRights[1][1] = 0;
	}
	else {
		castleRights[0][0] = 0;
		castleRights[0][1] = 0;
	}
}

void	updateRookCastlingRights(char rook, int castleRights[2][2], int rookPos[2]) {
	if (rook == 'r' && rookPos[0] == 0 && rookPos[1] == 0)
		castleRights[1][1] = 0;
	if (rook == 'r' && rookPos[0] == 0 && rookPos[1] == 7)
		castleRights[1][0] = 0;
	if (rook == 'R' && rookPos[0] == 7 && rookPos[1] == 0)
		castleRights[0][1] = 0;
	if (rook == 'R' && rookPos[0] == 7 && rookPos[1] == 7)
		castleRights[0][0] = 0;
}

void	updateKingCastlingRights(char king, int castleRights[2][2]) {
	if (king == 'k') {
		castleRights[1][0] = 0;
		castleRights[1][1] = 0;
	}
	else {
		castleRights[0][0] = 0;
		castleRights[0][1] = 0;
	}
}

void	applySpecialMoves(char board[BOARD_H][BOARD_W], t_moves *moves, \
							int target[2], int castleRights[2][2]) {
	while (moves) {
		if (moves->target[0] == target[0] && moves->target[1] == target[1])
			break ;
		moves = moves->next;
	}
	if (moves == NULL)
		return ;
	if (abs(moves->specialMove) == 1)
		extraMoveEnPassant(board, target[0] + moves->specialMove, target[1]);
	else if (moves->specialMove == 2)
		extraMoveCastling(board, target, castleRights);
	else if (tolower(board[target[0]][target[1]]) == 'r')
		updateRookCastlingRights(board[target[0]][target[1]], castleRights, target);
	else if (tolower(board[target[0]][target[1]]) == 'k')
		updateKingCastlingRights(board[target[0]][target[1]], castleRights);
}

int	isCheckmate(char board[BOARD_H][BOARD_W], t_boardInfo *info) {
	if (isCheckmateBlack(board, info)) {
		printf("%sCheckmate, white wins!\n", CURSOR_DOWN_2);
		return 1;
	}
	if (isCheckmateWhite(board, info)) {
		printf("%sCheckmate, black wins!\n", CURSOR_DOWN_2);
		return 1;
	}
	return 0;
}

void	makeMove(char board[BOARD_H][BOARD_W], t_boardInfo *info) {
	movePieceToTarget(board, info->selectedPiece, info->cursor);
	applySpecialMoves(board, info->moves, info->cursor, info->castleRights);
	updateLastMove(info, info->selectedPiece, info->cursor);
	info->turn = info->turn == 1 ? 0 : 1;
}

int	handleSelection(char board[BOARD_H][BOARD_W], t_boardInfo *info) {
	if (info->cursor[0] == info->selectedPiece[0] && \
		info->cursor[1] == info->selectedPiece[1])
		deselectPiece(info);
	else if (isHighlightedMove(info->moves, info->cursor[0], info->cursor[1])) {
		makeMove(board, info);
		deselectPiece(info);
		if (isCheckmate(board, info))
			return 1;
	}
	else if (board[info->cursor[0]][info->cursor[1]] == '.')
		deselectPiece(info);
	else {
		deselectPiece(info);
		selectPiece(info);
		getMovesAtSquare(&info->moves, board, info->selectedPiece, info);
	}
	return 0;
}

int	main(void) {
	char			board[BOARD_H][BOARD_W];
	struct termios	original;
	char			c;
	t_boardInfo		info;
	int				exitCondition = 0;

	initialiseEmptyBoard(board);
	initialiseHighlight(&info);
	loadFEN(board, "rnb1kb1r/pppppppp/8/8/3q4/8/PPPP1nPP/RNB2RK1 b kq", &info);
	displayBoard(board, &info);
	enableRawMode(&original);
	if (isCheckmate(board, &info)) {
		disableRawMode(&original);
		return 0;
	}
	while (read(STDIN_FILENO, &c, 1) && c != 'q' && exitCondition == 0) {
		if (c == ' ')
			exitCondition = handleSelection(board, &info);
		else if (c == '\033')
			handleArrowKey(c, &info);
		displayBoard(board, &info);
	}
	printf(CURSOR_DOWN_2);
	cleanupMoves(&info.moves);
	disableRawMode(&original);
	return 0;
}
