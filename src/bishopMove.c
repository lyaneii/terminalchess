/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   bishopMove.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: kwchu <kwchu@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/01 14:02:07 by kwchu         #+#    #+#                 */
/*   Updated: 2024/05/01 15:18:02 by kwchu         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include "board.h"
#include "move.h"

static int	bishopCount(board_t *board, moveInfo_t *move, char bishop) {
	int	count = 0;
	int	offsetP = abs(move->targetCoords[0] - move->targetCoords[1]);
	int	offsetN = move->targetCoords[0] + move->targetCoords[1];

	for (int i = BOARD_START + 1; i < BOARD_END; i++) {
		if (i == move->targetCoords[1])
			continue ;
		for (int j = 1; j < BOARD_W - 1; j++) {
			if (j == move->targetCoords[0])
				continue ;
			if (abs(i - j) != offsetP && i + j != offsetN)
				continue ;
			if (board->area[i][j] == bishop)
				count++;
		}
	}
	return count;
}

static int	getBishopAtFile(board_t *board, moveInfo_t *move, int file, char bishop) {
	int	offsetP = abs(move->targetCoords[0] - move->targetCoords[1]);
	int	offsetN = move->targetCoords[0] + move->targetCoords[1];

	if (getFilePieceCount(board, bishop, file) != 1)
		return -1;
	move->selfCoords[0] = file;
	for (int i = BOARD_START + 1; i < BOARD_END; i++) {
		if (abs(i - file) != offsetP && i + file != offsetN)
			continue ;
		if (board->area[i][file] == bishop) {
			move->selfCoords[1] = i;
			return 0;
		}
	}
	return -1;
}

static int	getBishopAtRank(board_t *board, moveInfo_t *move, int rank, char bishop) {
	int	offsetP = abs(move->targetCoords[0] - move->targetCoords[1]);
	int	offsetN = move->targetCoords[0] + move->targetCoords[1];

	if (getRankPieceCount(board, bishop, rank) != 1)
		return -1;
	move->selfCoords[1] = rank;
	for (int i = 1; i < BOARD_W - 1; i++) {
		if (abs(i - rank) != offsetP && i + rank != offsetN)
			continue ;
		if (board->area[rank][i] == bishop) {
			move->selfCoords[0] = i;
			return 0;
		}
	}
	return -1;
}

static int	getBishopCoords(board_t *board, moveInfo_t *move, int file, int rank, char bishop) {
	int	offsetP = abs(move->targetCoords[0] - move->targetCoords[1]);
	int	offsetN = move->targetCoords[0] + move->targetCoords[1];

	if (rank != 0 && file != 0) {
		if (board->area[file][rank] != bishop)
			return -1;
		else {
			move->selfCoords[0] = file;
			move->selfCoords[1] = rank;
			return 0;
		}
	}
	for (int i = BOARD_START + 1; i < BOARD_END; i++) {
		if (i == move->targetCoords[1])
			continue ;
		for (int j = 1; j < BOARD_W - 1; j++) {
			if (j == move->targetCoords[0])
				continue ;
			if (abs(i - j) != offsetP && i + j != offsetN)
				continue ;
			if (board->area[i][j] == bishop) {
				move->selfCoords[1] = i;
				move->selfCoords[0] = j;
				return 0;
			}
		}
	}
	return -1;
}

int	rangeCheckBishop(board_t *board, moveInfo_t *move, const char *input) {
	char	bishop = board->turn == 0 ? 'b' : 'B';
	int		count = bishopCount(board, move, bishop);
	size_t	len = strlen(input);

	if (count == 0)
		return -1;
	if (move->capture == 0 && len > 5)
		return -1;
	if (move->capture == 1 && len > 6)
		return -1;
	if (count == 1)
		return getBishopCoords(board, move, 0, 0, bishop);
	if (len - move->capture == 4) {
		if (strchr(COLUMN, input[1]))
			return getBishopAtFile(board, move, convertCoordToIndex(input[1]), bishop);
		else if (strchr(ROW, input[1]))
			return getBishopAtRank(board, move, convertCoordToIndex(input[1]), bishop);
		return -1;
	}
	if (len - move->capture == 5) {
		if (!strchr(COLUMN, input[1]) || !strchr(ROW, input[2]))
			return -1;
		return getBishopCoords(board, move, convertCoordToIndex(input[2]), convertCoordToIndex(input[1]), bishop);
	}
	return -1;
}
