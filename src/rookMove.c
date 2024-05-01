/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   rookMove.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: kwchu <kwchu@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/01 17:42:22 by kwchu         #+#    #+#                 */
/*   Updated: 2024/05/01 18:28:18 by kwchu         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include "board.h"
#include "move.h"

static int	rookCount(board_t *board, moveInfo_t *move, char rook) {
	int	count = 0;

	for (int i = BOARD_START + 1; i < BOARD_END; i++) {
		if (board->area[i][move->targetCoords[0]] == rook)
			count++;
		else if (i == move->targetCoords[1]) {
			for (int j = 1; j < BOARD_W - 1; j++) {
				if (j == move->targetCoords[0])
					continue ;
				if (board->area[i][j] == rook)
					count++;
			}
		}
	}
	return count;
}

static int	getRookAtFile(board_t *board, moveInfo_t *move, int file, char rook) {
	if (getFilePieceCount(board, rook, file) != 1)
		return -1;
	move->selfCoords[0] = file;
	for (int i = BOARD_START + 1; i < BOARD_END; i++) {
		if (board->area[i][file] == rook) {
			move->selfCoords[1] = i;
			return 0;
		}
	}
	return -1;
}

static int	getRookAtRank(board_t *board, moveInfo_t *move, int rank, char rook) {
	if (getRankPieceCount(board, rook, rank) != 1)
		return -1;
	move->selfCoords[1] = rank;
	for (int i = 1; i < BOARD_W - 1; i++) {
		if (board->area[rank][i] == rook) {
			move->selfCoords[0] = i;
			return 0;
		}
	}
	return -1;
}

static int	getRookCoords(board_t *board, moveInfo_t *move, int file, int rank, char rook) {
	if (rank != 0 && file != 0) {
		if (board->area[file][rank] != rook)
			return -1;
		else {
			move->selfCoords[0] = file;
			move->selfCoords[1] = rank;
			return 0;
		}
	}
	for (int i = BOARD_START + 1; i < BOARD_END; i++) {
		if (board->area[i][move->targetCoords[0]] == rook) {
			move->selfCoords[0] = move->targetCoords[0];
			move->selfCoords[1] = i;
			return 0;
		}
		else if (i == move->targetCoords[1]) {
			for (int j = 1; j < BOARD_W - 1; j++) {
				if (j == move->targetCoords[0])
					continue ;
				if (board->area[i][j] == rook) {
					move->selfCoords[1] = i;
					move->selfCoords[0] = j;
					return 0;
				}
			}
		}
	}
	return -1;
}

int	rangeCheckRook(board_t *board, moveInfo_t *move, const char *input) {
	char	rook = board->turn == 0 ? 'r' : 'R';
	int		count = rookCount(board, move, rook);
	size_t	len = strlen(input);

	if (count == 0)
		return -1;
	if (move->capture == 0 && len > 5)
		return -1;
	if (move->capture == 1 && len > 6)
		return -1;
	if (count == 1)
		return getRookCoords(board, move, 0, 0, rook);
	if (len - move->capture == 4) {
		if (strchr(COLUMN, input[1]))
			return getRookAtFile(board, move, convertCoordToIndex(input[1]), rook);
		else if (strchr(ROW, input[1]))
			return getRookAtRank(board, move, convertCoordToIndex(input[1]), rook);
		return -1;
	}
	if (len - move->capture == 5) {
		if (!strchr(COLUMN, input[1]) || !strchr(ROW, input[2]))
			return -1;
		return getRookCoords(board, move, convertCoordToIndex(input[2]), convertCoordToIndex(input[1]), rook);
	}
	return -1;
}
