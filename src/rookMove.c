/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   rookMove.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: kwchu <kwchu@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/12 01:59:11 by kwchu         #+#    #+#                 */
/*   Updated: 2024/05/12 02:00:04 by kwchu         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "moves.h"

void	getRookMoves(t_moves **moves, char board[BOARD_H][BOARD_W], \
					int start[2]) {
	int	range[3][3] = {
		{0,8,0},
		{8,0,8},
		{0,8,0}
	};
	getPossibleMoves(moves, board, start, range);
}
