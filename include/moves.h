/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   moves.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: kwchu <kwchu@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/08 13:22:16 by kwchu         #+#    #+#                 */
/*   Updated: 2024/05/09 14:59:13 by kwchu         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef TERMINAL_CHESS_MOVES_H
# define TERMINAL_CHESS_MOVES_H

typedef struct s_moves {
	int				target[2];
	struct s_moves	*next;
}	t_moves;

typedef struct s_display {
	int		cursor[2];
	int		selectedPiece[2];
	int		lastMove[2][2];
	t_moves	*moves;
}	t_display;

void	getMovesAtSquare(t_moves **moves, char board[BOARD_H][BOARD_W], int originalPosition[2]);
void	cleanupMoves(t_moves **moves);

#endif