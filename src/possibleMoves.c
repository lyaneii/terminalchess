/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   possibleMoves.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: kwchu <kwchu@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/12 01:37:05 by kwchu         #+#    #+#                 */
/*   Updated: 2024/05/13 19:10:37 by kwchu         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <ctype.h>
#include "moves.h"

int	isWithinBounds(int target[2]) {
	if (target[0] < 0 || target[0] >= BOARD_H)
		return 0;
	if (target[1] < 0 || target[1] >= BOARD_W)
		return 0;
	return 1;
}

int	isValidTarget(char target, char self) {
	if (target == '.')
		return 1;
	if (isupper(self) && isupper(target))
		return 0;
	if (islower(self) && islower(target))
		return 0;
	return 1;
}

static void	checkNorth(t_moves **moves, char board[BOARD_H][BOARD_W], \
					int originalStart[2], int distance, char piece) {
	int	start[2] = {originalStart[0], originalStart[1]};

	if (distance == 0)
		return ;
	while (distance > 0) {
		start[0]--;
		if (!isWithinBounds(start))
			return ;
		if (tolower(piece) == 'p' && board[start[0]][start[1]] != '.')
			return ;
		if (isValidTarget(board[start[0]][start[1]], piece))
			addMove(moves, newMove(originalStart, start, 0));
		else
			return ;
		if (board[start[0]][start[1]] != '.')
			return ;
		distance--;
	}
}

static void	checkWest(t_moves **moves, char board[BOARD_H][BOARD_W], \
					int originalStart[2], int distance, char piece) {
	int	start[2] = {originalStart[0], originalStart[1]};

	if (distance == 0)
		return ;
	while (distance > 0) {
		start[1]--;
		if (!isWithinBounds(start))
			return ;
		if (isValidTarget(board[start[0]][start[1]], piece))
			addMove(moves, newMove(originalStart, start, 0));
		else
			return ;
		if (board[start[0]][start[1]] != '.')
			return ;
		distance--;
	}
}

static void	checkEast(t_moves **moves, char board[BOARD_H][BOARD_W], \
					int originalStart[2], int distance, char piece) {
	int	start[2] = {originalStart[0], originalStart[1]};

	if (distance == 0)
		return ;
	while (distance > 0) {
		start[1]++;
		if (!isWithinBounds(start))
			return ;
		if (isValidTarget(board[start[0]][start[1]], piece))
			addMove(moves, newMove(originalStart, start, 0));
		else
			return ;
		if (board[start[0]][start[1]] != '.')
			return ;
		distance--;
	}
}

static void	checkSouth(t_moves **moves, char board[BOARD_H][BOARD_W], \
					int originalStart[2], int distance, char piece) {
	int	start[2] = {originalStart[0], originalStart[1]};

	if (distance == 0)
		return ;
	while (distance > 0) {
		start[0]++;
		if (!isWithinBounds(start))
			return ;
		if (tolower(piece) == 'p' && board[start[0]][start[1]] != '.')
			return ;
		if (isValidTarget(board[start[0]][start[1]], piece))
			addMove(moves, newMove(originalStart, start, 0));
		else
			return ;
		if (board[start[0]][start[1]] != '.')
			return ;
		distance--;
	}
}

static void	checkNorthWest(t_moves **moves, char board[BOARD_H][BOARD_W], \
					int originalStart[2], int distance, char piece) {
	int	start[2] = {originalStart[0], originalStart[1]};

	if (distance == 0)
		return ;
	while (distance > 0) {
		start[0]--;
		start[1]--;
		if (!isWithinBounds(start))
			return ;
		if (tolower(piece) == 'p' && board[start[0]][start[1]] == '.')
			return ;
		if (isValidTarget(board[start[0]][start[1]], piece))
			addMove(moves, newMove(originalStart, start, 0));
		else
			return ;
		if (board[start[0]][start[1]] != '.')
			return ;
		distance--;
	}
}

static void	checkNorthEast(t_moves **moves, char board[BOARD_H][BOARD_W], \
					int originalStart[2], int distance, char piece) {
	int	start[2] = {originalStart[0], originalStart[1]};

	if (distance == 0)
		return ;
	while (distance > 0) {
		start[0]--;
		start[1]++;
		if (!isWithinBounds(start))
			return ;
		if (tolower(piece) == 'p' && board[start[0]][start[1]] == '.')
			return ;
		if (isValidTarget(board[start[0]][start[1]], piece))
			addMove(moves, newMove(originalStart, start, 0));
		else
			return ;
		if (board[start[0]][start[1]] != '.')
			return ;
		distance--;
	}
}

static void	checkSouthWest(t_moves **moves, char board[BOARD_H][BOARD_W], \
					int originalStart[2], int distance, char piece) {
	int	start[2] = {originalStart[0], originalStart[1]};

	if (distance == 0)
		return ;
	while (distance > 0) {
		start[0]++;
		start[1]--;
		if (!isWithinBounds(start))
			return ;
		if (tolower(piece) == 'p' && board[start[0]][start[1]] == '.')
			return ;
		if (isValidTarget(board[start[0]][start[1]], piece))
			addMove(moves, newMove(originalStart, start, 0));
		else
			return ;
		if (board[start[0]][start[1]] != '.')
			return ;
		distance--;
	}
}

static void	checkSouthEast(t_moves **moves, char board[BOARD_H][BOARD_W], \
					int originalStart[2], int distance, char piece) {
	int	start[2] = {originalStart[0], originalStart[1]};

	if (distance == 0)
		return ;
	while (distance > 0) {
		start[0]++;
		start[1]++;
		if (!isWithinBounds(start))
			return ;
		if (tolower(piece) == 'p' && board[start[0]][start[1]] == '.')
			return ;
		if (isValidTarget(board[start[0]][start[1]], piece))
			addMove(moves, newMove(originalStart, start, 0));
		else
			return ;
		if (board[start[0]][start[1]] != '.')
			return ;
		distance--;
	}
}

void	getPossibleMoves(t_moves **moves, char board[BOARD_H][BOARD_W], \
						int start[2], int direction[3][3]) {
	char piece = board[start[0]][start[1]];

	checkNorthWest(moves, board, start, direction[0][0], piece);
	checkNorth(moves, board, start, direction[0][1], piece);
	checkNorthEast(moves, board, start, direction[0][2], piece);
	checkWest(moves, board, start, direction[1][0], piece);
	checkEast(moves, board, start, direction[1][2], piece);
	checkSouthWest(moves, board, start, direction[2][0], piece);
	checkSouth(moves, board, start, direction[2][1], piece);
	checkSouthEast(moves, board, start, direction[2][2], piece);
}
