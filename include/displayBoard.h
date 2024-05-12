/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   displayBoard.h                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: kwchu <kwchu@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/12 17:40:44 by kwchu         #+#    #+#                 */
/*   Updated: 2024/05/12 17:58:22 by kwchu         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef TERMINALCHESS_DISPLAYBOARD_H
# define TERMINALCHESS_DISPLAYBOARD_H
# include "moves.h"

void	displayBoard(const char board[BOARD_H][BOARD_W], t_boardInfo *highlight);
#endif
