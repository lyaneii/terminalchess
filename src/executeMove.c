/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executeMove.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: kwchu <kwchu@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/04/28 23:00:14 by kwchu         #+#    #+#                 */
/*   Updated: 2024/05/01 17:29:30 by kwchu         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include "move.h"
#include "colours.h"

static int	getSign(int coord1, int coord2) {
	if (coord2 == coord1)
		return 0;
	return coord2 - coord1 < 0 ? 1 : -1;
}

static int	getTargetCoords(board_t *board, moveInfo_t *move, const char *input) {
	size_t	i = strlen(input) - 1;

	if (i < 1 || !strchr(ROW, input[i]) || !strchr(COLUMN, input[i - 1]))
		return -1;
	move->targetCoords[1] = convertCoordToIndex(input[i]);
	move->targetCoords[0] = convertCoordToIndex(input[i - 1]);
	if (move->capture == 0 && board->area[move->targetCoords[1]][move->targetCoords[0]] != '.')
		return -1;
	if (move->capture == 1) {
		if (board->area[move->targetCoords[1]][move->targetCoords[0]] == '.')
			return -1;
		if (board->turn == 0 && islower(board->area[move->targetCoords[1]][move->targetCoords[0]]))
			return -1;
		if (board->turn == 1 && isupper(board->area[move->targetCoords[1]][move->targetCoords[0]]))
			return -1;
	}
	return 0;
}

static int	getSelfCoords(board_t *board, moveInfo_t *move, const char *input) {
	if (strchr(COLUMN, input[0]))
		return rangeCheckPawn(board, move, input);
	else if (input[0] == 'N')
		return rangeCheckKnight(board, move, input);
	else if (input[0] == 'B')
		return rangeCheckBishop(board, move, input);
	else if (input[0] == 'Q')
		return -1;
	else if (input[0] == 'R')
		return -1;
	else if (input[0] == 'K')
		return -1;
	return -1;
}

static int	isCapture(const char *input) {
	if (!strchr(input, 'x'))
		return 0;
	else if (strchr(input, 'x') == strrchr(input, 'x'))
		return 1;
	return -1;
}

static int	pathIsUnobstructed(board_t *board, moveInfo_t *move) {
	int	rankSign = getSign(move->targetCoords[1], move->selfCoords[1]);
	int	fileSign = getSign(move->targetCoords[0], move->selfCoords[0]);
	int	currentRank = move->selfCoords[1] + rankSign;
	int	currentFile = move->selfCoords[0] + fileSign;

	if (tolower(board->area[move->selfCoords[1]][move->selfCoords[0]]) == 'n')
		return 0;
	while (currentRank != move->targetCoords[1] || currentFile != move->targetCoords[0]) {
		if (board->area[currentRank][currentFile] != '.')
			return -1;
		currentRank += rankSign;
		currentFile += fileSign;
	}
	return 0;
}

static int	findMoveCoords(board_t *board, moveInfo_t *move, const char *input) {
	if (getTargetCoords(board, move, input) == -1)
		return -1;
	if (getSelfCoords(board, move, input) == -1)
		return -1;
	return 0;
}

static int	determineMove(board_t *board, moveInfo_t *move, const char *input) {
	if (!strchr("abcdefghNBQRK", input[0]))
		return -1;
	move->capture = isCapture(input);
	if (move->capture == -1)
		return -1;
	if (findMoveCoords(board, move, input) == -1)
		return -1;
	return pathIsUnobstructed(board, move);
}

int executeMove(board_t *board, const char *input) {
	moveInfo_t	move;

	move.valid = determineMove(board, &move, input);
	if (move.valid == -1) {
		printf("\033[0K%sinvalid move%s", RED, RESET);
		return -1;
	}
	printf("\033[0K%svalid move%s", GREEN, RESET);
	board->area[move.targetCoords[1]][move.targetCoords[0]] = board->area[move.selfCoords[1]][move.selfCoords[0]];
	board->area[move.selfCoords[1]][move.selfCoords[0]] = '.';
	return 0;
}
