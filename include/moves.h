/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   moves.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: kwchu <kwchu@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/08 13:22:16 by kwchu         #+#    #+#                 */
/*   Updated: 2024/05/08 13:33:29 by kwchu         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef TERMINAL_CHESS_MOVES_H
# define TERMINAL_CHESS_MOVES_H

typedef struct s_display {
	int	cursor[2];
	int	selectedPiece[2];
	int	*highlightMoves;
}	t_display;

#endif