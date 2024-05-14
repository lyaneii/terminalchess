/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   getMoves.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: kwchu <kwchu@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/12 01:40:39 by kwchu         #+#    #+#                 */
/*   Updated: 2024/05/14 17:20:03 by kwchu         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <ctype.h>
#include "moves.h"

void	getMovesAtSquare(t_moves **moves, char board[BOARD_H][BOARD_W], \
						int originalPosition[2], t_boardInfo *info) {
	int	position[2] = {originalPosition[0], originalPosition[1]};
	t_moves	*attackers;

	if (info->turn == 1 && islower(board[position[0]][position[1]]))
		return ;
	if (info->turn == 0 && isupper(board[position[0]][position[1]]))
		return ;
	if (board[position[0]][position[1]] == '.')
		return ;
	else if (tolower(board[position[0]][position[1]]) == 'p')
		getPawnMoves(moves, board, position, info->lastMove);
	else if (tolower(board[position[0]][position[1]]) == 'r')
		getRookMoves(moves, board, position);
	else if (tolower(board[position[0]][position[1]]) == 'q')
		getQueenMoves(moves, board, position);
	else if (tolower(board[position[0]][position[1]]) == 'b')
		getBishopMoves(moves, board, position);
	else if (tolower(board[position[0]][position[1]]) == 'k')
		getKingMoves(moves, board, position, info->castleRights);
	else if (tolower(board[position[0]][position[1]]) == 'n')
		getKnightMoves(moves, board, position);
	attackers = getPiecesAttackingKing(board, originalPosition);
	cleanupMoves(&attackers);
	removeMovesNotBlockingCheck(moves, board);
}
