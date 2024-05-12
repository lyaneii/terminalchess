/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   displayBoard.h                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: kwchu <kwchu@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/12 17:40:44 by kwchu         #+#    #+#                 */
/*   Updated: 2024/05/12 17:41:10 by kwchu         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef TERMINAL_CHESS_DISPLAY_BOARD_H
# define TERMINAL_CHESS_DISPLAY_BOARD_H
# include "moves.h"

void	displayBoard(const char board[BOARD_H][BOARD_W], t_boardInfo *highlight);
#endif
