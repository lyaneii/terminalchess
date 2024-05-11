/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pawnMove.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: kwchu <kwchu@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/08 13:23:22 by kwchu         #+#    #+#                 */
/*   Updated: 2024/05/11 15:34:40 by kwchu         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "defines.h"
#include "moves.h"
#include <ctype.h>
#include <stdlib.h>
#define START_RANK_W 6
#define START_RANK_B 1
#define EN_PASSANT_RANK_W 3
#define EN_PASSANT_RANK_B 4

t_moves	*newMove(int target[2], int specialMove) {
	t_moves	*move;

	move = malloc(sizeof(t_moves));
	if (!move)
		return NULL;
	move->target[0] = target[0];
	move->target[1] = target[1];
	move->specialMove = specialMove;
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
			addMove(moves, newMove(start, 0));
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
			addMove(moves, newMove(start, 0));
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
			addMove(moves, newMove(start, 0));
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
			addMove(moves, newMove(start, 0));
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
			addMove(moves, newMove(start, 0));
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
			addMove(moves, newMove(start, 0));
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
			addMove(moves, newMove(start, 0));
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
			addMove(moves, newMove(start, 0));
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

int	enPassantIsPossible(char board[BOARD_H][BOARD_W], int start[2], int lastMove[2][2]) {
	if (tolower(board[lastMove[1][0]][lastMove[1][1]]) != 'p')
		return 0;
	if (start[0] == EN_PASSANT_RANK_W && abs(lastMove[1][1] - start[1]) == 1) {
		if (lastMove[0][0] == START_RANK_B)
			return 1;
	}
	else if (start[0] == EN_PASSANT_RANK_B && abs(lastMove[1][1] - start[1]) == 1) {
		if (lastMove[0][0] == START_RANK_W)
			return 1;
	}
	return 0;
}

void	getPawnMoves(t_moves **moves, char board[BOARD_H][BOARD_W], \
					int start[2], int lastMove[2][2]) {
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
		if (enPassantIsPossible(board, start, lastMove))
			addMove(moves, newMove((int[2]){lastMove[1][0] + 1, lastMove[1][1]}, -1));
	}
	else {
		getPossibleMoves(moves, board, start, captRangeWhite);
		if (pawnIsOnStartingRank(start[0], piece))
			getPossibleMoves(moves, board, start, moveRangeWhite);
		else {
			moveRangeWhite[0][1]--;
			getPossibleMoves(moves, board, start, moveRangeWhite);
		}
		if (enPassantIsPossible(board, start, lastMove))
			addMove(moves, newMove((int[2]){lastMove[1][0] - 1, lastMove[1][1]}, 1));
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
			addMove(moves, newMove(knightPos[i], 0));
	}
}

void	removeKnightMoves(char board[BOARD_H][BOARD_W], t_moves **moves) {
	t_moves	*remove;
	t_moves	*current = *moves;

	while (current && current->next) {
		if (board[current->next->target[0]][current->next->target[1]] == 'n' || \
			board[current->next->target[0]][current->next->target[1]] == 'N' ) {
			remove = current->next;
			current->next = remove->next;
			free(remove);
		}
		else
			current = current->next;
	}
	current = *moves;
	if (current && (board[current->target[0]][current->target[1]] == 'n' || \
		board[current->target[0]][current->target[1]] == 'N')) {
		*moves = current->next;
		free(current);
	}
}

void	removePawnMoves(char board[BOARD_H][BOARD_W], t_moves **moves) {
	t_moves	*remove;
	t_moves	*current = *moves;

	while (current && current->next) {
		if (board[current->next->target[0]][current->next->target[1]] == 'p' || \
			board[current->next->target[0]][current->next->target[1]] == 'P' ) {
			remove = current->next;
			current->next = remove->next;
			free(remove);
		}
		else
			current = current->next;
	}
	current = *moves;
	if (current && (board[current->target[0]][current->target[1]] == 'p' || \
		board[current->target[0]][current->target[1]] == 'P')) {
		*moves = current->next;
		free(current);
	}
}

int	isOpponentsKnight(char target, char self) {
	if (isupper(self) && target == 'n')
		return 1;
	if (islower(self) && target == 'N')
		return 1;
	return 0;
}

int	isOpponentsPawn(char target, char self) {
	if (isupper(self) && target == 'p')
		return 1;
	if (islower(self) && target == 'P')
		return 1;
	return 0;
}

void	removeEmptySquareMoves(char board[BOARD_H][BOARD_W], t_moves **moves) {
	t_moves	*remove;
	t_moves	*current = *moves;

	while (current && current->next) {
		if (board[current->next->target[0]][current->next->target[1]] == '.') {
			remove = current->next;
			current->next = remove->next;
			free(remove);
		}
		else
			current = current->next;
	}
	current = *moves;
	if (current && board[current->target[0]][current->target[1]] == '.') {
		*moves = current->next;
		free(current);
	}
}

void	getPiecesAttackingSquare(t_moves **moves, char board[BOARD_H][BOARD_W], int target[2], int side) {
	char piece = board[target[0]][target[1]];
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
	int	pawnDirection = side == 1 ? 1 : -1;
	int	pawnPos[2][2] = {
		{target[0] + pawnDirection, target[1] - 1},
		{target[0] + pawnDirection, target[1] + 1}
	};

	if (piece == '.' && side == 1)
		piece = 'k';
	else if (piece == '.' && side == 0)
		piece = 'K';
	checkNorthWest(moves, board, target, 8, piece);
	checkNorth(moves, board, target, 8, piece);
	checkNorthEast(moves, board, target, 8, piece);
	checkWest(moves, board, target, 8, piece);
	checkEast(moves, board, target, 8, piece);
	checkSouthWest(moves, board, target, 8, piece);
	checkSouth(moves, board, target, 8, piece);
	checkSouthEast(moves, board, target, 8, piece);
	removeKnightMoves(board, moves);
	removePawnMoves(board, moves);
	for (int i = 0; i < 8; i++) {
		if (!isWithinBounds(knightPos[i]))
			continue ;
		if (isOpponentsKnight(board[knightPos[i][0]][knightPos[i][1]], piece))
			addMove(moves, newMove(knightPos[i], 0));
	}
	for (int i = 0; i < 2; i++) {
		if (!isWithinBounds(pawnPos[i]))
			continue ;
		if (isOpponentsPawn(board[pawnPos[i][0]][pawnPos[i][1]], piece))
			addMove(moves, newMove(pawnPos[i], 0));
	}
	removeEmptySquareMoves(board, moves);
}

void	getKingPosition(char board[BOARD_H][BOARD_W], int side, int kingPos[2]) {
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

t_moves	*getPiecesAttackingKing(char board[BOARD_H][BOARD_W], int piece[2]) {
	int		side = islower(board[piece[0]][piece[1]]) ? 1 : 0;
	int		king[2] = {0,0};
	t_moves	*attackers = NULL;

	getKingPosition(board, side, king);
	getPiecesAttackingSquare(&attackers, board, king, side);
	return attackers;
}

void	copyBoard(char dest[BOARD_H][BOARD_W], char src[BOARD_H][BOARD_W]) {
	for (int i = 0; i < BOARD_H; i++) {
		for (int j = 0; j < BOARD_W; j++)
			dest[i][j] = src[i][j];
	}
}

void	tryMove(char board[BOARD_H][BOARD_W], int self[2], int target[2]) {
	board[target[0]][target[1]] = board[self[0]][self[1]];
	board[self[0]][self[1]] = '.';
}

int	moveBlocksCheck(int target[2], char board[BOARD_H][BOARD_W], int piece[2]) {
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

void	cleanupMoves(t_moves **moves) {
	t_moves	*tmp;

	while (*moves) {
		tmp = *moves;
		*moves = (*moves)->next;
		free(tmp);
	}
	*moves = NULL;
}

void	getMovesAtSquare(t_moves **moves, char board[BOARD_H][BOARD_W], int originalPosition[2], \
						int lastMove[2][2]) {
	int	position[2] = {originalPosition[0], originalPosition[1]};
	t_moves	*attackers;

	if (board[position[0]][position[1]] == '.')
		return ;
	else if (tolower(board[position[0]][position[1]]) == 'p')
		getPawnMoves(moves, board, position, lastMove);
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
	attackers = getPiecesAttackingKing(board, originalPosition);
	cleanupMoves(&attackers);
	removeMovesNotBlockingCheck(moves, board, originalPosition);
}
