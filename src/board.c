/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   board.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: kwchu <kwchu@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/04/28 21:38:08 by kwchu         #+#    #+#                 */
/*   Updated: 2024/05/01 13:37:30 by kwchu         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdio.h>
#include "piece.h"
#include "board.h"
#include "colours.h"

static void	createBorder(board_t *board) {
	for (int i = 0; i < BOARD_H; i++) {
		if (i == 0 || i == BOARD_H - 1 || i == BOARD_START || i == BOARD_END) {
			board->area[i][0] = '[';
			board->area[i][BOARD_W - 1] = ']';
			for (int j = 1; j < BOARD_W - 1; j++) {
				board->area[i][j] = '=';
			}
		}
		else {
			board->area[i][0] = '|';
			board->area[i][BOARD_W - 1] = '|';
		}
	}
}

static void	initStartingPosition(board_t *board) {
	for (int i = 1; i < BOARD_H - 1; i++) {
		if (i == BOARD_START || i == BOARD_END)
			continue ;
		for (int j = 1; j < BOARD_W - 1; j++) {
			board->area[i][j] = '.';
		}
	}
	for (int i = 1; i < BOARD_W - 1; i++) {
		board->area[BOARD_START + 1][i] = START_PIECES_B[i - 1];
		board->area[BOARD_START + 2][i] = 'P';
		board->area[BOARD_END - 1][i] = START_PIECES_W[i - 1];
		board->area[BOARD_END - 2][i] = 'p';
	}
}

static void	displayCoords(board_t *board) {
	char coord = 'a';

	for (int i = 1; i < BOARD_W - 1; i++) {
		board->area[BOARD_START][i] = coord;
		board->area[BOARD_END][i] = coord++;
	}
	coord = '8';
	for (int i = BOARD_START + 1; i < BOARD_END; i++) {
		board->area[i][0] = coord;
		board->area[i][BOARD_W - 1] = coord--;
	}
}

void	initBoard(board_t *board, int turn, int coords) {
	createBorder(board);
	if (coords)
		displayCoords(board);
	initStartingPosition(board);
	board->turn = turn;
}

void	drawBoard(board_t board) {
	printf("\033[u");
	for (int i = 0; i < BOARD_H; i++) {
		for (int j = 0; j < BOARD_W; j++) {
			if ((i > BOARD_START && i < BOARD_END) && isPiece(board.area[i][j]))
				drawPiece(board.area[i][j], i, j);
			else {
				if ((i == 0 && board.turn == 1) || \
					(i == BOARD_H - 1 && board.turn == 0))
					printf(RED);
				printf("%c", board.area[i][j]);
				printf(RESET);
			}
			printf(" ");
		}
		printf("\n");
	}
}
