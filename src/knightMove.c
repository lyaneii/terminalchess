/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   knightMove.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: kwchu <kwchu@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/04/29 21:35:20 by kwchu         #+#    #+#                 */
/*   Updated: 2024/05/01 15:13:43 by kwchu         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include "board.h"
#include "move.h"

static int	knightCount(board_t *board, moveInfo_t *move, char knight) {
	int	count = 0;
	int	offset = abs(move->targetCoords[0] - move->targetCoords[1]) % 2 == 0 ? 0 : 1;

	for (int i = move->targetCoords[1] - 2; i <= move->targetCoords[1] + 2; i++) {
		if (i <= BOARD_START || i == move->targetCoords[1] || i >= BOARD_END)
			continue ;
		for (int j = move->targetCoords[0] - 2; j <= move->targetCoords[0] + 2; j++) {
			if (j < 1 || j == move->targetCoords[0] || j > 8)
				continue ;
			if (j - i != 0 && abs(j - i) % 2 == offset)
				continue ;
			if (board->area[i][j] == knight)
				count++;
		}
	}
	return count;
}

static int	getKnightAtRank(board_t *board, moveInfo_t *move, int rank, char knight) {
	int	offset = abs(move->targetCoords[1] - rank);

	if (offset == 0)
		return -1;
	offset = offset == 1 ? 2 : 1;
	if (getRankPieceCount(board, knight, rank) != 1)
		return -1;
	move->selfCoords[1] = rank;
	if (board->area[rank][move->targetCoords[0] - offset] == knight) {
		move->selfCoords[0] = move->targetCoords[0] - offset;
	}
	else if (board->area[rank][move->targetCoords[0] + offset] == knight)
		move->selfCoords[0] = move->targetCoords[0] + offset;
	else
		return -1;
	return 0;
}

static int	getKnightAtFile(board_t *board, moveInfo_t *move, int file, char knight) {
	int	offset = abs(move->targetCoords[0] - file);

	if (offset == 0)
		return -1;
	offset = offset == 1 ? 2 : 1;
	if (getFilePieceCount(board, knight, file) != 1)
		return -1;
	move->selfCoords[0] = file;
	if (board->area[move->targetCoords[1] - offset][file] == knight) {
		move->selfCoords[1] = move->targetCoords[1] - offset;
	}
	else if (board->area[move->targetCoords[1] + offset][file] == knight)
		move->selfCoords[1] = move->targetCoords[1] + offset;
	else
		return -1;
	return 0;
}

static int	getKnightCoords(board_t *board, moveInfo_t *move, int file, int rank, char knight) {
	int	offset = abs(move->targetCoords[0] - move->targetCoords[1]) % 2 == 0 ? 0 : 1;

	if (rank != 0 && file != 0) {
		if (board->area[file][rank] != knight)
			return -1;
		else {
			move->selfCoords[0] = file;
			move->selfCoords[1] = rank;
			return 0;
		}
	}
	for (int i = move->targetCoords[1] - 2; i <= move->targetCoords[1] + 2; i++) {
		if (i <= BOARD_START || i == move->targetCoords[1] || i >= BOARD_END)
			continue ;
		for (int j = move->targetCoords[0] - 2; j <= move->targetCoords[0] + 2; j++) {
			if (j < 1 || j == move->targetCoords[0] || j > 8)
				continue ;
			if (j - i != 0 && abs(j - i) % 2 == offset)
				continue ;
			if (board->area[i][j] == knight) {
				move->selfCoords[1] = i;
				move->selfCoords[0] = j;
				return 0;
			}
		}
	}
	return -1;
}

int	rangeCheckKnight(board_t *board, moveInfo_t *move, const char *input) {
	char	knight = board->turn == 0 ? 'n' : 'N';
	int		count = knightCount(board, move, knight);
	size_t	len = strlen(input);

	if (count == 0)
		return -1;
	if (move->capture == 0 && len > 5)
		return -1;
	if (move->capture == 1 && len > 6)
		return -1;
	if (count == 1)
		return getKnightCoords(board, move, 0, 0, knight);
	if (len - move->capture == 4) {
		if (strchr(COLUMN, input[1]))
			return getKnightAtFile(board, move, convertCoordToIndex(input[1]), knight);
		else if (strchr(ROW, input[1]))
			return getKnightAtRank(board, move, convertCoordToIndex(input[1]), knight);
		return -1;
	}
	if (len - move->capture == 5) {
		if (!strchr(COLUMN, input[1]) || !strchr(ROW, input[2]))
			return -1;
		return getKnightCoords(board, move, convertCoordToIndex(input[2]), convertCoordToIndex(input[1]), knight);
	}
	return -1;
}
