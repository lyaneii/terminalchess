/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   moves.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: kwchu <kwchu@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/08 13:22:16 by kwchu         #+#    #+#                 */
/*   Updated: 2024/05/13 20:30:13 by kwchu         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef TERMINALCHESS_MOVES_H
# define TERMINALCHESS_MOVES_H
# include "defines.h"

typedef struct s_moves {
	int				self[2];
	int				target[2];
	int				specialMove;
	struct s_moves	*next;
}	t_moves;

typedef struct s_boardInfo {
	int		cursor[2];
	int		selectedPiece[2];
	int		lastMove[2][2];
	int		turn;
	int		castleRights[2][2];
	t_moves	*moves;
}	t_boardInfo;


t_moves	*newMove(int self[2], int target[2], int specialMove);
void	addMove(t_moves **head, t_moves *move);
void	cleanupMoves(t_moves **moves);

int		isWithinBounds(int target[2]);
int		isValidTarget(char target, char self);
void	getMovesAtSquare(t_moves **moves, char board[BOARD_H][BOARD_W], \
						int originalPosition[2], t_boardInfo *info);
void	getPossibleMoves(t_moves **moves, char board[BOARD_H][BOARD_W], \
						int start[2], int direction[3][3]);

void	getPawnMoves(t_moves **moves, char board[BOARD_H][BOARD_W], \
					int start[2], int lastMove[2][2]);
void	getKingMoves(t_moves **moves, char board[BOARD_H][BOARD_W], \
					int start[2], int castleRights[2][2]);
void	getKnightMoves(t_moves **moves, char board[BOARD_H][BOARD_W], int start[2]);
void	getBishopMoves(t_moves **moves, char board[BOARD_H][BOARD_W], int start[2]);
void	getQueenMoves(t_moves **moves, char board[BOARD_H][BOARD_W], int start[2]);
void	getRookMoves(t_moves **moves, char board[BOARD_H][BOARD_W], int start[2]);

t_moves	*getPiecesAttackingKing(char board[BOARD_H][BOARD_W], int piece[2]);
void	getPiecesAttackingSquare(t_moves **moves, char board[BOARD_H][BOARD_W], \
								int target[2], int side);
void	removeMovesNotBlockingCheck(t_moves **moves, char board[BOARD_H][BOARD_W], int piece[2]);
void	applySpecialMoves(char board[BOARD_H][BOARD_W], t_moves *moves, \
							t_boardInfo *info);

int		isCheckmate(char board[BOARD_H][BOARD_W], t_boardInfo *info);
void	makeMove(char board[BOARD_H][BOARD_W], t_boardInfo *info);
void	copyBoard(char dest[BOARD_H][BOARD_W], char src[BOARD_H][BOARD_W]);
void	tryMove(char board[BOARD_H][BOARD_W], int self[2], int target[2]);
#endif