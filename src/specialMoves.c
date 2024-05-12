/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   specialMoves.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: kwchu <kwchu@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/12 17:34:52 by kwchu         #+#    #+#                 */
/*   Updated: 2024/05/12 17:55:26 by kwchu         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <ctype.h>
#include <stdlib.h>
#include "moves.h"

void	extraMoveEnPassant(char board[BOARD_H][BOARD_W], int row, int col) {
	board[row][col] = '.';
}

static void	extraMoveCastling(char board[BOARD_H][BOARD_W], int target[2], int castleRights[2][2]) {
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

static void	updateRookCastlingRights(char rook, int castleRights[2][2], int rookPos[2]) {
	if (rook == 'r' && rookPos[0] == 0 && rookPos[1] == 0)
		castleRights[1][1] = 0;
	if (rook == 'r' && rookPos[0] == 0 && rookPos[1] == 7)
		castleRights[1][0] = 0;
	if (rook == 'R' && rookPos[0] == 7 && rookPos[1] == 0)
		castleRights[0][1] = 0;
	if (rook == 'R' && rookPos[0] == 7 && rookPos[1] == 7)
		castleRights[0][0] = 0;
}

static void	updateKingCastlingRights(char king, int castleRights[2][2]) {
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
