/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   board.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: kwchu <kwchu@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/04/28 21:39:06 by kwchu         #+#    #+#                 */
/*   Updated: 2024/05/01 13:38:59 by kwchu         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef TERMINALCHESS_BOARD_H
# define TERMINALCHESS_BOARD_H

# define BOARD_W 10
# define BOARD_H 16
# define BOARD_START 3
# define BOARD_END 12
# define START_PIECES_W "rnbqkbnr"
# define START_PIECES_B "RNBQKBNR"
# define BOARD_FILL "○"
# define BOARD_FILL_ALTERNATE "●"

typedef struct {
	char	area[BOARD_H][BOARD_W];
	int		turn;
}	board_t;

void	initBoard(board_t *board, int turn, int coords);
void	drawBoard(board_t board);

#endif