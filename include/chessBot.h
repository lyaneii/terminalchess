/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   chessBot.h                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: kwchu <kwchu@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/13 19:16:17 by kwchu         #+#    #+#                 */
/*   Updated: 2024/05/13 22:47:22 by kwchu         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef TERMINALCHESS_CHESSBOT_H
# define TERMINALCHESS_CHESSBOT_H
# include "moves.h"

# define VALUE_KING 20000
# define VALUE_QUEEN 900
# define VALUE_ROOK 500
# define VALUE_BISHOP 320
# define VALUE_KNIGHT 300
# define VALUE_PAWN 100

typedef struct s_engine {
	int		side;
	int		maxDepth;
	int		maxSelfEval;
	int		maxResponseEval;
	t_moves	*bestMove;
}	t_engine;

void	engineMakeMove(t_boardInfo *info, char board[BOARD_H][BOARD_W]);

#endif