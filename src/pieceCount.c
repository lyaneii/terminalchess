/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pieceCount.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: kwchu <kwchu@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/01 14:59:35 by kwchu         #+#    #+#                 */
/*   Updated: 2024/05/01 14:59:52 by kwchu         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "board.h"

int	getRankPieceCount(board_t *board, char piece, int rank) {
	int	count = 0;

	for (int i = 1; i < BOARD_W - 2; i++) {
		if (board->area[rank][i] == piece)
			count++;
	}
	return count;
}

int	getFilePieceCount(board_t *board, char piece, int file) {
	int	count = 0;

	for (int i = BOARD_START + 1; i < BOARD_END; i++) {
		if (board->area[i][file] == piece)
			count++;
	}
	return count;
}
