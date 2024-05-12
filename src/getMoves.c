/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   getMoves.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: kwchu <kwchu@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/12 01:40:39 by kwchu         #+#    #+#                 */
/*   Updated: 2024/05/12 02:09:43 by kwchu         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <ctype.h>
#include "moves.h"

void	getMovesAtSquare(t_moves **moves, char board[BOARD_H][BOARD_W], \
						int originalPosition[2], int lastMove[2][2]) {
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
