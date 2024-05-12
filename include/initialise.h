/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   initialise.h                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: kwchu <kwchu@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/12 02:11:28 by kwchu         #+#    #+#                 */
/*   Updated: 2024/05/12 13:22:29 by kwchu         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef TERMINAL_CHESS_INITIALISE_H
# define TERMINAL_CHESS_INITIALISE_H

void	initialiseHighlight(t_boardInfo *info);
void	loadFEN(char board[BOARD_H][BOARD_W], const char *FEN, t_boardInfo *info);
void	initialiseEmptyBoard(char board[BOARD_H][BOARD_W]);
#endif