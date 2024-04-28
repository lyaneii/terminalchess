/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pawnMove.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: kwchu <kwchu@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/04/28 21:37:45 by kwchu         #+#    #+#                 */
/*   Updated: 2024/04/28 23:05:32 by kwchu         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <ctype.h>
#include <string.h>
#include "board.h"
#include "move.h"

static int	isStartPawnMove(struct board_s *board, const int *coords) {
	if (board->turn == 0 && coords[1] == convertCoordToIndex('4')) {
		if (board->area[coords[1] + 1][coords[0]] == 'p' || \
			board->area[coords[1] + 2][coords[0]] == 'p')
			return 0;
	}
	else if (board->turn == 1 && coords[1] == convertCoordToIndex('5')) {
		if (board->area[coords[1] - 1][coords[0]] == 'P' || \
			board->area[coords[1] - 2][coords[0]] == 'P')
			return 0;
	}
	return -1;
}

static int	checkPawnTarget(struct board_s *board, const char targetPiece, const int *coords, const int column, int capture) {
	int	captureDirection = 0;
	
	if (targetPiece != '.')
		captureDirection = islower(targetPiece) ? -1 : 1;
	if (board->turn == 0 && captureDirection == -1)
		return -1;
	if (board->turn == 1 && captureDirection == 1)
		return -1;
	if (capture == 1 && targetPiece == '.')
		return -1;
	if (capture == 0 && targetPiece != '.')
		return -1;
	if (capture == 1) {
		if (captureDirection == 1 && board->area[coords[1] + captureDirection][column] != 'p')
			return -1;
		if (captureDirection == -1 && board->area[coords[1] + captureDirection][column] != 'P')
			return -1;
	}
	if (capture == 0) {
		if (isStartPawnMove(board, coords) == 0)
			return 0;
		if (board->turn == 0 && board->area[coords[1] + 1][coords[0]] != 'p')
			return -1;
		if (board->turn == 1 && board->area[coords[1] - 1][coords[0]] != 'P')
			return -1;
	}
	return 0;
}

static int	validatePawnMove(struct board_s *board, const char *target, int column, int capture) {
	int 	targetCoords[2];
	char	targetPiece;

	if (capture == 1 && strlen(target) != 2)
		return -1;
	if (capture == 1) {
		targetCoords[0] = convertCoordToIndex(target[0]);
		targetCoords[1] = convertCoordToIndex(target[1]);
	}
	else {
		targetCoords[0] = column;
		targetCoords[1] = convertCoordToIndex(target[0]);
	}
	targetPiece = board->area[targetCoords[1]][targetCoords[0]];
	return checkPawnTarget(board, targetPiece, targetCoords, column, capture);
}

int	pawnMove(struct board_s *board, const char *move) {
	int	column;
	int	capture = 0;

	column = convertCoordToIndex(move[0]);
	if (move[1] == 'x')
		capture = 1;
	return validatePawnMove(board, move + capture + 1, column, capture);
}
