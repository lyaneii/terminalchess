/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pawnMove.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: kwchu <kwchu@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/04/28 21:37:45 by kwchu         #+#    #+#                 */
/*   Updated: 2024/04/30 02:39:25 by kwchu         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include "board.h"
#include "move.h"

static int	checkPawnStartingMove(board_t *board, moveInfo_t *move, const int sign, const char pawn) {
	if (board->area[move->targetCoords[1] + (2 * sign)][move->targetCoords[0]] == pawn && \
		board->area[move->targetCoords[1] + (1 * sign)][move->targetCoords[0]] == '.')
		return 0;
	return -1;
}

static int	pawnNonCaptureMove(board_t *board, moveInfo_t *move) {
	int		sign = -1;
	char	targetIndex = '5';
	char	pawn = 'P';
	
	if (board->turn == 0) {
		sign = 1;
		targetIndex = '4';
		pawn = 'p';
	}
	if (board->area[move->targetCoords[1] + (1 * sign)][move->targetCoords[0]] == pawn)
		move->selfCoords[1] = move->targetCoords[1] + (1 * sign);
	else if (move->targetCoords[1] == convertCoordToIndex(targetIndex)) {
		if (checkPawnStartingMove(board, move, sign, pawn) == 0)
			move->selfCoords[1] = move->targetCoords[1] + (2 * sign);
		else
			return -1;
	}
	else
		return -1;
	return 0;
}

static int	pawnCaptureMove(board_t *board, moveInfo_t *move) {
	int		sign = -1;
	char	pawn = 'P';

	if (abs(move->selfCoords[0] - move->targetCoords[0]) != 1)
		return -1;
	if (board->turn == 0) {
		sign = 1;
		pawn = 'p';
	}
	if (board->area[move->targetCoords[1] + (1 * sign)][move->selfCoords[0]] == pawn)
		move->selfCoords[1] = move->targetCoords[1] + (1 * sign);
	else
		return -1;
	return 0;
}

int	rangeCheckPawn(board_t *board, moveInfo_t *move, const char *input) {
	if (move->capture == 0 && strlen(input) != 2)
		return -1;
	else if (move->capture == 1 && strlen(input) != 4)
		return -1;
	move->selfCoords[0] = convertCoordToIndex(input[0]);
	if (move->capture == 0)
		return pawnNonCaptureMove(board, move);
	else
		return pawnCaptureMove(board, move);
}
