/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   board.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: kwchu <kwchu@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/04/28 21:39:06 by kwchu         #+#    #+#                 */
/*   Updated: 2024/04/28 23:31:24 by kwchu         ########   odam.nl         */
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

struct	board_s {
	char	area[BOARD_H][BOARD_W];
	char	*lastMove;
	int		turn;
};

void	initBoard(struct board_s *board, int turn, int coords);
void	drawBoard(struct board_s board);

#endif