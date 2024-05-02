/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   kingMove.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: kwchu <kwchu@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/02 15:52:09 by kwchu         #+#    #+#                 */
/*   Updated: 2024/05/02 15:53:30 by kwchu         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include "board.h"
#include "move.h"

static int	getQueenCoords(board_t *board, moveInfo_t *move, int file, int rank, char queen) {
	int	offsetP = abs(move->targetCoords[0] - move->targetCoords[1]);
	int	offsetN = move->targetCoords[0] + move->targetCoords[1];

	if (rank != 0 && file != 0) {
		if (board->area[file][rank] != queen)
			return -1;
		else {
			move->selfCoords[0] = file;
			move->selfCoords[1] = rank;
			return 0;
		}
	}
	for (int i = BOARD_START + 1; i < BOARD_END; i++) {
		for (int j = 1; j < BOARD_W - 1; j++) {
			if ((abs(i - j) != offsetP && i + j != offsetN) && \
				(i != move->targetCoords[1] && j != move->targetCoords[0]))
				continue ;
			if (board->area[i][j] == queen) {
				move->selfCoords[1] = i;
				move->selfCoords[0] = j;
				return 0;
			}
		}
	}
	return -1;
}

int	rangeCheckQueen(board_t *board, moveInfo_t *move, const char *input) {
	char	queen = board->turn == 0 ? 'q' : 'Q';
	int		count = queenCount(board, move, queen);
	size_t	len = strlen(input);

	if (count == 0)
		return -1;
	if (move->capture == 0 && len > 4)
		return -1;
	if (move->capture == 1 && len > 3)
		return -1;
	if (count == 1)
		return getQueenCoords(board, move, 0, 0, queen);
	if (len - move->capture == 4) {
		if (strchr(COLUMN, input[1]))
			return getQueenAtFile(board, move, convertCoordToIndex(input[1]), queen);
		else if (strchr(ROW, input[1]))
			return getQueenAtRank(board, move, convertCoordToIndex(input[1]), queen);
		return -1;
	}
	if (len - move->capture == 5) {
		if (!strchr(COLUMN, input[1]) || !strchr(ROW, input[2]))
			return -1;
		return getQueenCoords(board, move, convertCoordToIndex(input[2]), convertCoordToIndex(input[1]), queen);
	}
	return -1;
}
