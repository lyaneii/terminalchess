/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   knightMove.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: kwchu <kwchu@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/12 01:55:32 by kwchu         #+#    #+#                 */
/*   Updated: 2024/05/12 02:01:16 by kwchu         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "moves.h"

void	getKnightMoves(t_moves **moves, char board[BOARD_H][BOARD_W], int start[2]) {
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
