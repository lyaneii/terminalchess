/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   kingMove.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: kwchu <kwchu@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/12 01:56:12 by kwchu         #+#    #+#                 */
/*   Updated: 2024/05/12 14:19:58 by kwchu         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <ctype.h>
#include "moves.h"

static int	castlingPathIsClear(char board[BOARD_H][BOARD_W], int start[2], int direction) {
	int	current[2] = {start[0], start[1] + direction};

	while (current[1] > 0 && current[1] < BOARD_W - 1) {
		if (board[current[0]][current[1]] != '.')
			return 0;
		current[1] += direction;
	}
	return 1;
}

static int	castlesThroughCheck(char board[BOARD_H][BOARD_W], int start[2], \
								int side, int direction) {
	int	current[2] = {start[0], start[1]};
	t_moves *attackers = NULL;

	for (size_t i = 0; i < 2; i++) {
		current[1] += direction;
		getPiecesAttackingSquare(&attackers, board, current, side);
	}
	if (attackers == NULL)
		return 0;
	cleanupMoves(&attackers);
	return 1;
}

void	getCastlingMoves(t_moves **moves, char board[BOARD_H][BOARD_W], \
						int start[2], int castleRights[2][2]) {
	int side = islower(board[start[0]][start[1]]) ? 1 : 0;

	if (side == 1 && board[start[0]][start[1] + 3] != 'r');
	else if (side == 0 && board[start[0]][start[1] + 3] != 'R');
	else if (castleRights[side][0] == 1 && !castlesThroughCheck(board, start, side, 1) && \
			castlingPathIsClear(board, start, 1))
		addMove(moves, newMove((int[2]){start[0], start[1] + 2}, 2));
	if (side == 1 && board[start[0]][start[1] - 4] != 'r');
	else if (side == 0 && board[start[0]][start[1] - 4] != 'R');
	else if (castleRights[side][1] == 1 && !castlesThroughCheck(board, start, side, -1) && \
			castlingPathIsClear(board, start, -1))
		addMove(moves, newMove((int[2]){start[0], start[1] - 2}, 2));
}

void	getKingMoves(t_moves **moves, char board[BOARD_H][BOARD_W], \
					int start[2], int castleRights[2][2]) {
	int	range[3][3] = {
		{1,1,1},
		{1,0,1},
		{1,1,1}
	};
	getPossibleMoves(moves, board, start, range);
	getCastlingMoves(moves, board, start, castleRights);
}
