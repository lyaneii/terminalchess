/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   scanChecks.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: kwchu <kwchu@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/12 01:39:44 by kwchu         #+#    #+#                 */
/*   Updated: 2024/05/12 02:55:24 by kwchu         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <ctype.h>
#include "moves.h"

static void	copyBoard(char dest[BOARD_H][BOARD_W], char src[BOARD_H][BOARD_W]) {
	for (int i = 0; i < BOARD_H; i++) {
		for (int j = 0; j < BOARD_W; j++)
			dest[i][j] = src[i][j];
	}
}

static void	tryMove(char board[BOARD_H][BOARD_W], int self[2], int target[2]) {
	board[target[0]][target[1]] = board[self[0]][self[1]];
	board[self[0]][self[1]] = '.';
}

static int	moveBlocksCheck(int target[2], char board[BOARD_H][BOARD_W], int piece[2]) {
	char	copy[BOARD_H][BOARD_W];
	t_moves	*attackers;

	copyBoard(copy, board);
	tryMove(copy, piece, target);
	attackers = getPiecesAttackingKing(copy, target);
	if (attackers == NULL)
		return 1;
	cleanupMoves(&attackers);
	return 0;
}

static void	getKingPosition(char board[BOARD_H][BOARD_W], int side, int kingPos[2]) {
	char kingPiece = side == 1 ? 'k' : 'K';

	for (int i = 0; i < BOARD_H; i++) {
		for (int j = 0; j < BOARD_W; j++) {
			if (board[i][j] == kingPiece) {
				kingPos[0] = i;
				kingPos[1] = j;
				return ;
			}
		}
	}
}

void	removeMovesNotBlockingCheck(t_moves **moves, char board[BOARD_H][BOARD_W], int piece[2]) {
	t_moves	*remove;
	t_moves	*current = *moves;

	while (current && current->next) {
		if (!moveBlocksCheck(current->next->target, board, piece)) {
			remove = current->next;
			current->next = remove->next;
			free(remove);
		}
		else
			current = current->next;
	}
	current = *moves;
	if (current && !moveBlocksCheck(current->target, board, piece)) {
		*moves = current->next;
		free(current);
	}
}

t_moves	*getPiecesAttackingKing(char board[BOARD_H][BOARD_W], int piece[2]) {
	int		side = islower(board[piece[0]][piece[1]]) ? 1 : 0;
	int		king[2] = {0,0};
	t_moves	*attackers = NULL;

	getKingPosition(board, side, king);
	getPiecesAttackingSquare(&attackers, board, king, side);
	return attackers;
}
