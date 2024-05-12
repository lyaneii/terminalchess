/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   controls.h                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: kwchu <kwchu@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/12 17:32:24 by kwchu         #+#    #+#                 */
/*   Updated: 2024/05/12 17:55:10 by kwchu         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef TERMINAL_CHESS_CONTROLS_H
# define TERMINAL_CHESS_CONTROLS_H
# include "moves.h"

int		isHighlightedMove(t_moves *moves, int row, int col);
int		handleSelection(char board[BOARD_H][BOARD_W], t_boardInfo *info);
void	handleArrowKey(char c, t_boardInfo *highlight);
#endif