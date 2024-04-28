/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   move.h                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: kwchu <kwchu@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/04/28 22:58:29 by kwchu         #+#    #+#                 */
/*   Updated: 2024/04/28 23:41:07 by kwchu         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef TERMINALCHESS_MOVE_H
# define TERMINALCHESS_MOVE_H
# include "board.h"

int	convertCoordToIndex(char coord);
int	pawnMove(board_t *board, const char *move);
int executeMove(board_t *board, const char *move);

#endif