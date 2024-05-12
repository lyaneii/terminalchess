/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   specialMoves.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: kwchu <kwchu@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/12 17:34:52 by kwchu         #+#    #+#                 */
/*   Updated: 2024/05/12 23:47:20 by kwchu         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <ctype.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "moves.h"
#include "displayBoard.h"

void	extraMoveEnPassant(char board[BOARD_H][BOARD_W], int row, int col) {
	board[row][col] = '.';
}

static void	extraMoveCastling(char board[BOARD_H][BOARD_W], int target[2], int castleRights[2][2]) {
	int		castleSide = target[1] == 2 ? 0 : 1;
	int		rookOffset = target[1] == 2 ? 1 : -1;
	int 	rookCastlePos[2] = {0, 7};

	board[target[0]][target[1] + rookOffset] = board[target[0]][rookCastlePos[castleSide]];
	board[target[0]][rookCastlePos[castleSide]] = '.';
	if (board[target[0]][target[1] + rookOffset] == 'r') {
		castleRights[1][0] = 0;
		castleRights[1][1] = 0;
	}
	else {
		castleRights[0][0] = 0;
		castleRights[0][1] = 0;
	}
}

static void	updateRookCastlingRights(char rook, int castleRights[2][2], int rookPos[2]) {
	if (rook == 'r' && rookPos[0] == 0 && rookPos[1] == 0)
		castleRights[1][1] = 0;
	if (rook == 'r' && rookPos[0] == 0 && rookPos[1] == 7)
		castleRights[1][0] = 0;
	if (rook == 'R' && rookPos[0] == 7 && rookPos[1] == 0)
		castleRights[0][1] = 0;
	if (rook == 'R' && rookPos[0] == 7 && rookPos[1] == 7)
		castleRights[0][0] = 0;
}

static void	updateKingCastlingRights(char king, int castleRights[2][2]) {
	if (king == 'k') {
		castleRights[1][0] = 0;
		castleRights[1][1] = 0;
	}
	else {
		castleRights[0][0] = 0;
		castleRights[0][1] = 0;
	}
}

static void	wrapIndex(int *index, int size) {
	if (*index >= size)
		*index = 0;
	else if (*index < 0)
		*index = size - 1;
}

static void	handleArrowCycling(char input, char board[BOARD_H][BOARD_W], int target[2], \
								char promotionPiece[4], int *currentPiece) {
	if (read(STDIN_FILENO, &input, 1) && input == '[') {
		read(STDIN_FILENO, &input, 1);
		if (input == 'C') {
			(*currentPiece)++;
			wrapIndex(currentPiece, 4);
			board[target[0]][target[1]] = promotionPiece[*currentPiece];
		}
		else if (input == 'D') {
			(*currentPiece)--;
			wrapIndex(currentPiece, 4);
			board[target[0]][target[1]] = promotionPiece[*currentPiece];
		}
	}
}

static void	handleCharCycling(char input, char board[BOARD_H][BOARD_W], int target[2], \
								char promotionPiece[4], int *currentPiece) {
	if (input == CHAR_CONTROLS[1]) {
		(*currentPiece)--;
		wrapIndex(currentPiece, 4);
		board[target[0]][target[1]] = promotionPiece[*currentPiece];
	}
	else if (input == CHAR_CONTROLS[3]) {
		(*currentPiece)++;
		wrapIndex(currentPiece, 4);
		board[target[0]][target[1]] = promotionPiece[*currentPiece];
	}
}

static void	pickPromotionPiece(char board[BOARD_H][BOARD_W], t_boardInfo *info, int side) {
	char	promotionPiece[4] = "qrbn";
	int		currentPiece = 0;
	char	input;
	
	if (side == 0) {
		promotionPiece[0] = toupper(promotionPiece[0]);
		promotionPiece[1] = toupper(promotionPiece[1]);
		promotionPiece[2] = toupper(promotionPiece[2]);
		promotionPiece[3] = toupper(promotionPiece[3]);
	}
	board[info->cursor[0]][info->cursor[1]] = promotionPiece[0];
	displayBoard(board, info);
	while (read(STDIN_FILENO, &input, 1) && input != CHAR_SELECT) {
		if (input == '\033')
			handleArrowCycling(input, board, info->cursor, promotionPiece, &currentPiece);
		else if (strchr(CHAR_CONTROLS, input))
			handleCharCycling(input, board, info->cursor, promotionPiece, &currentPiece);
		displayBoard(board, info);
	}
}

static int	pawnIsOnPromotionRank(int rank, int side) {
	if (side == 1 && rank == 7)
		return 1;
	if (side == 0 && rank == 0)
		return 1;
	return 0;
}

static void extraMovePromotion(char pawn, char board[BOARD_H][BOARD_W], t_boardInfo *info) {
	int side = islower(pawn) ? 1 : 0;

	if (!pawnIsOnPromotionRank(info->cursor[0], side))
		return ;
	pickPromotionPiece(board, info, side);
}

void	applySpecialMoves(char board[BOARD_H][BOARD_W], t_moves *moves, \
							t_boardInfo *info) {
	
	while (moves) {
		if (moves->target[0] == info->cursor[0] && moves->target[1] == info->cursor[1])
			break ;
		moves = moves->next;
	}
	if (moves == NULL)
		return ;
	if (abs(moves->specialMove) == 1)
		extraMoveEnPassant(board, info->cursor[0] + moves->specialMove, info->cursor[1]);
	else if (moves->specialMove == 2)
		extraMoveCastling(board, info->cursor, info->castleRights);
	else if (tolower(board[info->cursor[0]][info->cursor[1]]) == 'r')
		updateRookCastlingRights(board[info->cursor[0]][info->cursor[1]], info->castleRights, info->cursor);
	else if (tolower(board[info->cursor[0]][info->cursor[1]]) == 'k')
		updateKingCastlingRights(board[info->cursor[0]][info->cursor[1]], info->castleRights);
	else if (tolower(board[info->cursor[0]][info->cursor[1]]) == 'p')
		extraMovePromotion(board[info->cursor[0]][info->cursor[1]], board, info);
}
