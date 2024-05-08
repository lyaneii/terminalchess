/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pawnMove.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: kwchu <kwchu@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/08 13:23:22 by kwchu         #+#    #+#                 */
/*   Updated: 2024/05/08 17:50:24 by kwchu         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "defines.h"
#include "moves.h"
#include <ctype.h>
#include <stdlib.h>
#define START_RANK_W 6
#define START_RANK_B 1

t_moves	*newMove(int target[2]) {
	t_moves	*move;

	move = malloc(sizeof(t_moves));
	if (!move)
		return NULL;
	move->target[0] = target[0];
	move->target[1] = target[1];
	move->next = NULL;
	return move;
}

void	addMove(t_moves **head, t_moves *move) {
	if (!move)
		return ;
	if (!*head)
		*head = move;
	else {
		move->next = *head;
		*head = move;
	}
}

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

int	pawnIsOnStartingRank(int rank, char pawn) {
	if (isupper(pawn) && rank == START_RANK_W)
		return 1;
	if (islower(pawn) && rank == START_RANK_B)
		return 1;
	return 0;
}

void	checkNorth(t_moves **moves, char board[BOARD_H][BOARD_W], \
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
			addMove(moves, newMove(start));
		else
			return ;
		if (board[start[0]][start[1]] != '.')
			return ;
		distance--;
	}
}

void	checkWest(t_moves **moves, char board[BOARD_H][BOARD_W], \
					int originalStart[2], int distance, char piece) {
	int	start[2] = {originalStart[0], originalStart[1]};

	if (distance == 0)
		return ;
	while (distance > 0) {
		start[1]--;
		if (!isWithinBounds(start))
			return ;
		if (isValidTarget(board[start[0]][start[1]], piece))
			addMove(moves, newMove(start));
		else
			return ;
		if (board[start[0]][start[1]] != '.')
			return ;
		distance--;
	}
}

void	checkEast(t_moves **moves, char board[BOARD_H][BOARD_W], \
					int originalStart[2], int distance, char piece) {
	int	start[2] = {originalStart[0], originalStart[1]};

	if (distance == 0)
		return ;
	while (distance > 0) {
		start[1]++;
		if (!isWithinBounds(start))
			return ;
		if (isValidTarget(board[start[0]][start[1]], piece))
			addMove(moves, newMove(start));
		else
			return ;
		if (board[start[0]][start[1]] != '.')
			return ;
		distance--;
	}
}

void	checkSouth(t_moves **moves, char board[BOARD_H][BOARD_W], \
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
			addMove(moves, newMove(start));
		else
			return ;
		if (board[start[0]][start[1]] != '.')
			return ;
		distance--;
	}
}

void	checkNorthWest(t_moves **moves, char board[BOARD_H][BOARD_W], \
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
			addMove(moves, newMove(start));
		else
			return ;
		if (board[start[0]][start[1]] != '.')
			return ;
		distance--;
	}
}

void	checkNorthEast(t_moves **moves, char board[BOARD_H][BOARD_W], \
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
			addMove(moves, newMove(start));
		else
			return ;
		if (board[start[0]][start[1]] != '.')
			return ;
		distance--;
	}
}

void	checkSouthWest(t_moves **moves, char board[BOARD_H][BOARD_W], \
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
			addMove(moves, newMove(start));
		else
			return ;
		if (board[start[0]][start[1]] != '.')
			return ;
		distance--;
	}
}

void	checkSouthEast(t_moves **moves, char board[BOARD_H][BOARD_W], \
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
			addMove(moves, newMove(start));
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

void	getPawnMoves(t_moves **moves, char board[BOARD_H][BOARD_W], \
					int start[2]) {
	char piece = board[start[0]][start[1]];
	int	captRangeBlack[3][3] = {
		{0,0,0},
		{0,0,0},
		{1,0,1}
	};
	int	moveRangeBlack[3][3] = {
		{0,0,0},
		{0,0,0},
		{0,2,0}
	};
	int	captRangeWhite[3][3] = {
		{1,0,1},
		{0,0,0},
		{0,0,0}
	};
	int	moveRangeWhite[3][3] = {
		{0,2,0},
		{0,0,0},
		{0,0,0}
	};

	if (islower(piece)) {
		getPossibleMoves(moves, board, start, captRangeBlack);
		if (pawnIsOnStartingRank(start[0], piece))
			getPossibleMoves(moves, board, start, moveRangeBlack);
		else {
			moveRangeBlack[2][1]--;
			getPossibleMoves(moves, board, start, moveRangeBlack);
		}
	}
	else {
		getPossibleMoves(moves, board, start, captRangeWhite);
		if (pawnIsOnStartingRank(start[0], piece))
			getPossibleMoves(moves, board, start, moveRangeWhite);
		else {
			moveRangeWhite[0][1]--;
			getPossibleMoves(moves, board, start, moveRangeWhite);
		}
	}
}

void	getRookMoves(t_moves **moves, char board[BOARD_H][BOARD_W], \
					int start[2]) {
	int	range[3][3] = {
		{0,8,0},
		{8,0,8},
		{0,8,0}
	};
	getPossibleMoves(moves, board, start, range);
}

void	getQueenMoves(t_moves **moves, char board[BOARD_H][BOARD_W], \
					int start[2]) {
	int	range[3][3] = {
		{8,8,8},
		{8,0,8},
		{8,8,8}
	};
	getPossibleMoves(moves, board, start, range);
}

void	getBishopMoves(t_moves **moves, char board[BOARD_H][BOARD_W], \
						int start[2]) {
	int	range[3][3] = {
		{8,0,8},
		{0,0,0},
		{8,0,8}
	};
	getPossibleMoves(moves, board, start, range);
}

void	getKingMoves(t_moves **moves, char board[BOARD_H][BOARD_W], \
					int start[2]) {
	int	range[3][3] = {
		{1,1,1},
		{1,0,1},
		{1,1,1}
	};
	getPossibleMoves(moves, board, start, range);
}

void	getKnightMoves(t_moves **moves, char board[BOARD_H][BOARD_W], \
						int start[2]) {
	int	range[2] = {2, 1};
	int	knightPos[8][2] = {
		{start[0] + range[0], start[1] + range[1]},
		{start[0] + -range[0], start[1] + range[1]},
		{start[0] + -range[0], start[1] + -range[1]},
		{start[0] + range[0], start[1] + -range[1]},
		{start[0] + range[1], start[1] + range[0]},
		{start[0] + -range[1], start[1] + range[0]},
		{start[0] + -range[1], start[1] + -range[0]},
		{start[0] + range[1], start[1] + -range[0]}
	};

	for (int i = 0; i < 8; i++) {
		if (!isWithinBounds(knightPos[i]))
			continue ;
		if (isValidTarget(board[knightPos[i][0]][knightPos[i][1]], board[start[0]][start[1]]))
			addMove(moves, newMove(knightPos[i]));
	}
}

void	cleanupMoves(t_moves **moves) {
	t_moves	*tmp;

	while (*moves) {
		tmp = *moves;
		*moves = (*moves)->next;
		free(tmp);
	}
	*moves = NULL;
}

void	getMovesAtSquare(t_moves **moves, char board[BOARD_H][BOARD_W], int originalPosition[2]) {
	int	position[2] = {originalPosition[0], originalPosition[1]};

	if (board[position[0]][position[1]] == '.')
		return ;
	else if (tolower(board[position[0]][position[1]]) == 'p')
		getPawnMoves(moves, board, position);
	else if (tolower(board[position[0]][position[1]]) == 'r')
		getRookMoves(moves, board, position);
	else if (tolower(board[position[0]][position[1]]) == 'q')
		getQueenMoves(moves, board, position);
	else if (tolower(board[position[0]][position[1]]) == 'b')
		getBishopMoves(moves, board, position);
	else if (tolower(board[position[0]][position[1]]) == 'k')
		getKingMoves(moves, board, position);
	else if (tolower(board[position[0]][position[1]]) == 'n')
		getKnightMoves(moves, board, position);
}
