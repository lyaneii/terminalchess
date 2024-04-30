/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   move.h                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: kwchu <kwchu@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/04/28 22:58:29 by kwchu         #+#    #+#                 */
/*   Updated: 2024/04/30 17:30:21 by kwchu         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef TERMINALCHESS_MOVE_H
# define TERMINALCHESS_MOVE_H
# define ROW "12345678"
# define COLUMN "abcdefgh"
# include "board.h"

typedef struct moveInfo_s {
	int	selfCoords[2];
	int	targetCoords[2];
	int	capture;
	int	valid;
}	moveInfo_t;

typedef struct moveList_s {
	char				*move;
	struct moveList_s	*next;
}	moveList_t;

int	convertCoordToIndex(char coord);
int executeMove(board_t *board, const char *move);
int	rangeCheckPawn(board_t *board, moveInfo_t *move, const char *input);
int	rangeCheckKnight(board_t *board, moveInfo_t *move, const char *input);
#endif