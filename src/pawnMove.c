/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pawnMove.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: kwchu <kwchu@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/08 13:23:22 by kwchu         #+#    #+#                 */
/*   Updated: 2024/05/12 01:55:08 by kwchu         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <ctype.h>
#include <stdlib.h>
#include "moves.h"

static int	pawnIsOnStartingRank(int rank, char pawn) {
	if (isupper(pawn) && rank == START_RANK_W)
		return 1;
	if (islower(pawn) && rank == START_RANK_B)
		return 1;
	return 0;
}

static int	enPassantIsPossible(char board[BOARD_H][BOARD_W], int start[2], int lastMove[2][2]) {
	if (tolower(board[lastMove[1][0]][lastMove[1][1]]) != 'p')
		return 0;
	if (start[0] == EN_PASSANT_RANK_W && abs(lastMove[1][1] - start[1]) == 1) {
		if (lastMove[0][0] == START_RANK_B)
			return 1;
	}
	else if (start[0] == EN_PASSANT_RANK_B && abs(lastMove[1][1] - start[1]) == 1) {
		if (lastMove[0][0] == START_RANK_W)
			return 1;
	}
	return 0;
}

void	getPawnMoves(t_moves **moves, char board[BOARD_H][BOARD_W], \
					int start[2], int lastMove[2][2]) {
	char piece = board[start[0]][start[1]];
	int	captRangeBlack[3][3] = {
		{0,0,0},
		{0,0,0},
		{1,0,1}
	};
	int	moveRangeBlack[3][3] = {
		{0,0,0},
		{0,0,0},
		{0,2,0}
	};
	int	captRangeWhite[3][3] = {
		{1,0,1},
		{0,0,0},
		{0,0,0}
	};
	int	moveRangeWhite[3][3] = {
		{0,2,0},
		{0,0,0},
		{0,0,0}
	};

	if (islower(piece)) {
		getPossibleMoves(moves, board, start, captRangeBlack);
		if (pawnIsOnStartingRank(start[0], piece))
			getPossibleMoves(moves, board, start, moveRangeBlack);
		else {
			moveRangeBlack[2][1]--;
			getPossibleMoves(moves, board, start, moveRangeBlack);
		}
		if (enPassantIsPossible(board, start, lastMove))
			addMove(moves, newMove((int[2]){lastMove[1][0] + 1, lastMove[1][1]}, -1));
	}
	else {
		getPossibleMoves(moves, board, start, captRangeWhite);
		if (pawnIsOnStartingRank(start[0], piece))
			getPossibleMoves(moves, board, start, moveRangeWhite);
		else {
			moveRangeWhite[0][1]--;
			getPossibleMoves(moves, board, start, moveRangeWhite);
		}
		if (enPassantIsPossible(board, start, lastMove))
			addMove(moves, newMove((int[2]){lastMove[1][0] - 1, lastMove[1][1]}, 1));
	}
}
