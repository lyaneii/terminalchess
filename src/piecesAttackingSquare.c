/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   piecesAttackingSquare.c                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: kwchu <kwchu@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/12 02:03:03 by kwchu         #+#    #+#                 */
/*   Updated: 2024/05/13 19:11:22 by kwchu         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <ctype.h>
#include "moves.h"

static int	targetCanAttackStraight(char target, int side, int distance) {
	if (target == '.')
		return 0;
	if (side == 0 && !strchr("rqk", target))
		return 0;
	if (side == 1 && !strchr("RQK", target))
		return 0;
	if (distance != 8 && tolower(target) == 'k')
		return 0;
	return 1;
}

static int	targetCanAttackDiagonally(char target, int side, int distance) {
	if (target == '.')
		return 0;
	if (side == 0 && !strchr("bqk", target))
		return 0;
	if (side == 1 && !strchr("BQK", target))
		return 0;
	if (distance != 8 && tolower(target) == 'k')
		return 0;
	return 1;
}

static int	targetIsOpponentKnight(char target, int side) {
	if (target == '.')
		return 0;
	if (side == 0 && target == 'n')
		return 1;
	if (side == 1 && target == 'N')
		return 1;
	return 0;
}

static void	getAttackersNorthWest(t_moves **attackers, char board[BOARD_H][BOARD_W], \
							int target[2], int side) {
	int	current[2] = {target[0], target[1]};
	int	distance = 8;

	while (distance > 0) {
		current[0]--;
		current[1]--;
		if (!isWithinBounds(current))
			return ;
		if (targetCanAttackDiagonally(board[current[0]][current[1]], side, distance))
			addMove(attackers, newMove(target, current, 0));
		if (board[current[0]][current[1]] != '.')
			return ;
		distance--;
	}
}

static void	getAttackersNorth(t_moves **attackers, char board[BOARD_H][BOARD_W], \
							int target[2], int side) {
	int	current[2] = {target[0], target[1]};
	int	distance = 8;

	while (distance > 0) {
		current[0]--;
		if (!isWithinBounds(current))
			return ;
		if (targetCanAttackStraight(board[current[0]][current[1]], side, distance))
			addMove(attackers, newMove(target, current, 0));
		if (board[current[0]][current[1]] != '.')
			return ;
		distance--;
	}
}

static void	getAttackersNorthEast(t_moves **attackers, char board[BOARD_H][BOARD_W], \
							int target[2], int side) {
	int	current[2] = {target[0], target[1]};
	int	distance = 8;

	while (distance > 0) {
		current[0]--;
		current[1]++;
		if (!isWithinBounds(current))
			return ;
		if (targetCanAttackDiagonally(board[current[0]][current[1]], side, distance))
			addMove(attackers, newMove(target, current, 0));
		if (board[current[0]][current[1]] != '.')
			return ;
		distance--;
	}
}

static void	getAttackersEast(t_moves **attackers, char board[BOARD_H][BOARD_W], \
							int target[2], int side) {
	int	current[2] = {target[0], target[1]};
	int	distance = 8;

	while (distance > 0) {
		current[1]++;
		if (!isWithinBounds(current))
			return ;
		if (targetCanAttackStraight(board[current[0]][current[1]], side, distance))
			addMove(attackers, newMove(target, current, 0));
		if (board[current[0]][current[1]] != '.')
			return ;
		distance--;
	}
}

static void	getAttackersSouthEast(t_moves **attackers, char board[BOARD_H][BOARD_W], \
							int target[2], int side) {
	int	current[2] = {target[0], target[1]};
	int	distance = 8;

	while (distance > 0) {
		current[0]++;
		current[1]++;
		if (!isWithinBounds(current))
			return ;
		if (targetCanAttackDiagonally(board[current[0]][current[1]], side, distance))
			addMove(attackers, newMove(target, current, 0));
		if (board[current[0]][current[1]] != '.')
			return ;
		distance--;
	}
}

static void	getAttackersSouth(t_moves **attackers, char board[BOARD_H][BOARD_W], \
							int target[2], int side) {
	int	current[2] = {target[0], target[1]};
	int	distance = 8;

	while (distance > 0) {
		current[0]++;
		if (!isWithinBounds(current))
			return ;
		if (targetCanAttackStraight(board[current[0]][current[1]], side, distance))
			addMove(attackers, newMove(target, current, 0));
		if (board[current[0]][current[1]] != '.')
			return ;
		distance--;
	}
}

static void	getAttackersSouthWest(t_moves **attackers, char board[BOARD_H][BOARD_W], \
							int target[2], int side) {
	int	current[2] = {target[0], target[1]};
	int	distance = 8;

	while (distance > 0) {
		current[0]++;
		current[1]--;
		if (!isWithinBounds(current))
			return ;
		if (targetCanAttackDiagonally(board[current[0]][current[1]], side, distance))
			addMove(attackers, newMove(target, current, 0));
		if (board[current[0]][current[1]] != '.')
			return ;
		distance--;
	}
}

static void	getAttackersWest(t_moves **attackers, char board[BOARD_H][BOARD_W], \
							int target[2], int side) {
	int	current[2] = {target[0], target[1]};
	int	distance = 8;

	while (distance > 0) {
		current[1]--;
		if (!isWithinBounds(current))
			return ;
		if (targetCanAttackStraight(board[current[0]][current[1]], side, distance))
			addMove(attackers, newMove(target, current, 0));
		if (board[current[0]][current[1]] != '.')
			return ;
		distance--;
	}
}

static void	getPawnAttackers(t_moves **attackers, char board[BOARD_H][BOARD_W], \
							int target[2], int side) {
	int	direction = side == 1 ? 1 : -1;
	int	current[2][2] = {
		{target[0] + direction, target[1] + 1},
		{target[0] + direction, target[1] - 1}
	};
	
	for (int i = 0; i < 2; i++) {
		if (!isWithinBounds(current[i]))
			continue ;
		if (side == 1 && board[current[i][0]][current[i][1]] == 'P')
			addMove(attackers, newMove(target, current[i], 0));
		else if (side == 0 && board[current[i][0]][current[i][1]] == 'p')
			addMove(attackers, newMove(target, current[i], 0));
	}
}

static void	getKnightAttackers(t_moves **attackers, char board[BOARD_H][BOARD_W], \
								int target[2], int side) {
	int	range[2] = {2, 1};
	int	knightPos[8][2] = {
		{target[0] + range[0], target[1] + range[1]},
		{target[0] + -range[0], target[1] + range[1]},
		{target[0] + -range[0], target[1] + -range[1]},
		{target[0] + range[0], target[1] + -range[1]},
		{target[0] + range[1], target[1] + range[0]},
		{target[0] + -range[1], target[1] + range[0]},
		{target[0] + -range[1], target[1] + -range[0]},
		{target[0] + range[1], target[1] + -range[0]}
	};

	for (int i = 0; i < 8; i++) {
		if (!isWithinBounds(knightPos[i]))
			continue ;
		if (targetIsOpponentKnight(board[knightPos[i][0]][knightPos[i][1]], side))
			addMove(attackers, newMove(target, knightPos[i], 0));
	}
}

void	getPiecesAttackingSquare(t_moves **attackers, char board[BOARD_H][BOARD_W], \
								int piece[2], int side) {
	getPawnAttackers(attackers, board, piece, side);
	getKnightAttackers(attackers, board, piece, side);
	getAttackersNorthWest(attackers, board, piece, side);
	getAttackersNorth(attackers, board, piece, side);
	getAttackersNorthEast(attackers, board, piece, side);
	getAttackersEast(attackers, board, piece, side);
	getAttackersSouthEast(attackers, board, piece, side);
	getAttackersSouth(attackers, board, piece, side);
	getAttackersSouthWest(attackers, board, piece, side);
	getAttackersWest(attackers, board, piece, side);
}
