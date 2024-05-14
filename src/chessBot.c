/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   chessBot.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: kwchu <kwchu@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/13 18:44:29 by kwchu         #+#    #+#                 */
/*   Updated: 2024/05/14 20:34:26 by kwchu         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <ctype.h>
#include <limits.h>
#include <stdio.h>
#include "chessBot.h"
#include "displayBoard.h"

static void	getAllMoves(t_moves **moves, t_boardInfo *info, char board[BOARD_H][BOARD_W]) {
	int (*pieceMatchesTurn)(int) = info->turn == 1 ? isupper : islower;

	for (int i = 0; i < BOARD_H; i++) {
		for (int j = 0; j < BOARD_W; j++) {
			if ((*pieceMatchesTurn)(board[i][j]))
				getMovesAtSquare(moves, board, (int[2]){i, j}, info);
		}
	}
}

static void	flipTable(int table[BOARD_H][BOARD_W]) {
	for (int i = 0; i < BOARD_H / 2; i++) {
		int tmp[BOARD_W] = {table[i][0], table[i][1], table[i][2], table[i][3],\
							table[i][4], table[i][5], table[i][6], table[i][7]};
		table[BOARD_H - i - 1][0] = tmp[0];
		table[BOARD_H - i - 1][1] = tmp[1];
		table[BOARD_H - i - 1][2] = tmp[2];
		table[BOARD_H - i - 1][3] = tmp[3];
		table[BOARD_H - i - 1][4] = tmp[4];
		table[BOARD_H - i - 1][5] = tmp[5];
		table[BOARD_H - i - 1][6] = tmp[6];
		table[BOARD_H - i - 1][7] = tmp[7];
	}
}

static int	knightMultiplier(int x, int y) {
	int	table[BOARD_H][BOARD_W] = {
		{-20,-20,0	,5	,5	,0	,-20,-20},
		{-10,0	,10	,15	,15	,10	,0	,-10},
		{5	,10	,50	,60	,60	,50	,10	,5	},
		{10	,30	,70	,80	,80	,70	,30	,10	},
		{10	,30	,70	,80	,80	,70	,30	,10	},
		{5	,10	,50	,60	,60	,50	,10	,5	},
		{-10,0	,10	,15	,15	,10	,0	,-10},
		{-20,-20,0	,5	,5	,0	,-20,-20}
	};

	return table[x][y];
}

static int	pawnMultiplier(int x, int y, int side) {
	int	table[BOARD_H][BOARD_W] = {
		{20	,20	,20	,20	,20	,20	,20	,20	},
		{100,100,100,100,100,100,100,100},
		{20	,30	,60	,80	,80	,60	,30	,20	},
		{10	,20	,30	,70	,70	,30	,20	,10	},
		{10	,10	,20	,40	,40	,20	,10	,10	},
		{5	,5	,5	,20	,20	,5	,5	,5	},
		{30	,20	,10	,-40,-40,10	,20	,30	},
		{0	,0	,0	,0	,0	,0	,0	,0	}
	};
	if (side == 1)
		flipTable(table);
	return table[x][y];
}

static int	rookMultiplier(int x, int y, int side) {
	int	table[BOARD_H][BOARD_W] = {
		{70	,70	,70	,70	,70	,70	,70	,70	},
		{80	,100,100,100,100,100,100,80	},
		{-10,20	,20	,20	,20	,20	,20	,-10},
		{-10,20	,20	,20	,20	,20	,20	,-10},
		{-10,20	,20	,20	,20	,20	,20	,-10},
		{-10,20	,20	,20	,20	,20	,20	,-10},
		{-10,20	,20	,20	,20	,20	,20	,-10},
		{20	,10	,10	,50	,50	,10	,10	,20	}
	};
	if (side == 1)
		flipTable(table);
	return table[x][y];
}

static int	bishopMultiplier(int x, int y, int side) {
	int	table[BOARD_H][BOARD_W] = {
		{-20,10	,10	,10	,10	,10	,10	,-20},
		{5	,30	,30	,20	,20	,30	,30	,5	},
		{5	,30	,35	,20	,20	,35	,30	,5	},
		{5	,60	,50	,55	,55	,50	,60	,5	},
		{5	,20	,80	,60	,60	,80	,20	,5	},
		{5	,30	,40	,35	,35	,40	,30	,5	},
		{5	,50	,20	,10	,10	,20	,50	,5	},
		{10	,50	,0	,5	,5	,0	,5	,10	}
	};
	if (side == 1)
		flipTable(table);
	return table[x][y];
}

static int	queenMultiplier(int x, int y, int side) {
	int	table[BOARD_H][BOARD_W] = {
		{-30,10	,10	,20	,20	,10	,10	,-30},
		{5	,30	,20	,50	,50	,20	,30	,5	},
		{5	,30	,65	,65	,65	,65	,30	,5	},
		{20	,60	,60	,70	,70	,60	,60	,20	},
		{30	,20	,70	,70	,70	,70	,20	,30	},
		{5	,50	,40	,50	,50	,40	,40	,5	},
		{5	,20	,20	,10	,10	,20	,20	,5	},
		{-30,10	,10	,20	,20	,10	,10	,-30}
	};
	if (side == 1)
		flipTable(table);
	return table[x][y];
}

static int	kingMultiplier(int x, int y, int side) {
	int	table[BOARD_H][BOARD_W] = {
		{0	,-10,-10,-50,-50,-10,-10,0	},
		{0	,-10,-10,-50,-50,-10,-10,0	},
		{0	,-5	,-5	,-50,-50,-5	,-5	,0	},
		{0	,-5	,-5	,-50,-50,-5	,-5	,0	},
		{5	,0	,0	,0	,0	,0	,0	,5	},
		{5	,5	,5	,0	,0	,5	,5	,5	},
		{15	,10	,10	,0	,0	,10	,15	,15	},
		{35	,40	,10	,20	,20	,10	,40	,35	}
	};
	if (side == 1)
		flipTable(table);
	return table[x][y];
}

static int	getPieceValue(char piece, int x, int y, int side) {
	piece = tolower(piece);
	if (piece == 'k')
		return VALUE_KING + kingMultiplier(x, y, side);
	if (piece == 'q')
		return VALUE_QUEEN + queenMultiplier(x, y, side);
	if (piece == 'r')
		return VALUE_ROOK + rookMultiplier(x, y, side);
	if (piece == 'b')
		return VALUE_BISHOP + bishopMultiplier(x, y, side);
	if (piece == 'n')
		return VALUE_KNIGHT + knightMultiplier(x, y);
	if (piece == 'p')
		return VALUE_PAWN + pawnMultiplier(x, y, side);
	return 0;
}

static int	getPieceValuesSide(char board[BOARD_H][BOARD_W], int side) {
	int (*pieceMatchesTurn)(int) = side == 1 ? isupper : islower;
	int	totalValue = 0;

	for (int i = 0; i < BOARD_H; i++) {
		for (int j = 0; j < BOARD_W; j++) {
			if ((*pieceMatchesTurn)(board[i][j]))
				totalValue += getPieceValue(board[i][j], i, j, side);
		}
	}
	return totalValue;
}

static int	evaluatePosition(char board[BOARD_H][BOARD_W], int side) {
	int	totalPieceValueBlack = getPieceValuesSide(board, 0);
	int	totalPieceValueWhite = getPieceValuesSide(board, 1);
	
	if (side == 1)
		return totalPieceValueBlack - totalPieceValueWhite;
	return totalPieceValueWhite - totalPieceValueBlack;
}

static void	calculateMoves(t_boardInfo *info, t_engine *engine, t_moves *rootMove, \
						char board[BOARD_H][BOARD_W], int depth) {
	t_moves	*current;
	t_moves	*moves = NULL;
	char	copy[BOARD_H][BOARD_W];
	int		currentEval = evaluatePosition(board, info->turn);

	if (info->turn != engine->side && currentEval < engine->maxResponseEval)
		return ;
	else {
		engine->bestMove = rootMove;
		engine->maxResponseEval = currentEval;
	}
	if (info->turn == engine->side && currentEval > engine->maxSelfEval) {
		engine->bestMove = rootMove;
		engine->maxSelfEval = currentEval;
	}
	if (depth >= engine->maxDepth)
		return ;
	
	getAllMoves(&moves, info, board);
	current = moves;
	while (current) {
		info->turn = info->turn == 1 ? 0 : 1;
		copyBoard(copy, board);
		tryMove(copy, current->self, current->target);
		calculateMoves(info, engine, rootMove, copy, depth + 1);
		current = current->next;
	}
	cleanupMoves(&moves);
}

void	engineMakeMove(t_boardInfo *info, char board[BOARD_H][BOARD_W]) {
	t_engine	engine;
	t_moves		*rootMoves = NULL;
	t_moves		*current;
	t_boardInfo	copyInfo = *info;
	char		copy[BOARD_H][BOARD_W];

	engine.side = info->turn;
	engine.maxSelfEval = evaluatePosition(board, engine.side);
	engine.maxResponseEval = INT_MIN;
	engine.maxDepth = 4;
	
	getAllMoves(&rootMoves, &copyInfo, board);
	current = rootMoves;
	while (current) {
		copyInfo.turn = copyInfo.turn == 1 ? 0 : 1;
		copyBoard(copy, board);
		tryMove(copy, current->self, current->target);
		calculateMoves(&copyInfo, &engine, current, copy, 1);
		current = current->next;
	}
	makeMove(board, engine.bestMove, info);
	cleanupMoves(&rootMoves);
}

// 0 - note first move
// 1 - do own move
// 2 - evaluate
// 3 - do enemy move
// 4 - evaluate
// 5 - continue until search depth has been reached
// 6 - if at search depth end eval > maxEval, bestmove = rootmove
// 