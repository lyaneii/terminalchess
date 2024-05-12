/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   controls.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: kwchu <kwchu@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/12 17:31:33 by kwchu         #+#    #+#                 */
/*   Updated: 2024/05/12 17:54:54 by kwchu         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <unistd.h>
#include <stdio.h>
#include "moves.h"

static void	movePieceToTarget(char board[BOARD_H][BOARD_W], int self[2], int target[2]) {
	board[target[0]][target[1]] = board[self[0]][self[1]];
	board[self[0]][self[1]] = '.';
}

static void	updateLastMove(t_boardInfo *highlight, int self[2], int target[2]) {
	highlight->lastMove[0][0] = self[0];
	highlight->lastMove[0][1] = self[1];
	highlight->lastMove[1][0] = target[0];
	highlight->lastMove[1][1] = target[1];
}

static void	makeMove(char board[BOARD_H][BOARD_W], t_boardInfo *info) {
	movePieceToTarget(board, info->selectedPiece, info->cursor);
	applySpecialMoves(board, info->moves, info->cursor, info->castleRights);
	updateLastMove(info, info->selectedPiece, info->cursor);
	info->turn = info->turn == 1 ? 0 : 1;
}

static void	deselectPiece(t_boardInfo *highlight) {
	highlight->selectedPiece[0] = -1;
	cleanupMoves(&highlight->moves);
}

static void	selectPiece(t_boardInfo *highlight) {
	highlight->selectedPiece[0] = highlight->cursor[0];
	highlight->selectedPiece[1] = highlight->cursor[1];
}

int	isHighlightedMove(t_moves *moves, int row, int col) {
	while (moves) {
		if (moves->target[0] == row && moves->target[1] == col)
			return 1;
		moves = moves->next;
	}
	return 0;
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
