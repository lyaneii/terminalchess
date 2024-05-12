/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   kingMove.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: kwchu <kwchu@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/12 01:56:12 by kwchu         #+#    #+#                 */
/*   Updated: 2024/05/12 01:56:38 by kwchu         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "moves.h"

void	getKingMoves(t_moves **moves, char board[BOARD_H][BOARD_W], int start[2]) {
	int	range[3][3] = {
		{1,1,1},
		{1,0,1},
		{1,1,1}
	};
	getPossibleMoves(moves, board, start, range);
}
