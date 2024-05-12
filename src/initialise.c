/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   initialise.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: kwchu <kwchu@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/12 02:11:17 by kwchu         #+#    #+#                 */
/*   Updated: 2024/05/12 02:15:02 by kwchu         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdio.h>
#include <ctype.h>
#include "moves.h"
#include "initialise.h"

void	initialiseHighlight(t_display *highlight) {
	highlight->cursor[0] = 0;
	highlight->cursor[1] = 0;
	highlight->selectedPiece[0] = -1;
	highlight->selectedPiece[1] = 0;
	highlight->lastMove[0][0] = -1;
	highlight->lastMove[0][1] = 0;
	highlight->lastMove[1][0] = 0;
	highlight->lastMove[1][1] = 0;
	highlight->moves = NULL;
}

void	loadFEN(char board[BOARD_H][BOARD_W], const char *FEN) {
	int	index[2] = {0, 0};

	for (size_t i = 0; FEN[i] && FEN[i] != ' '; i++) {
		if (FEN[i] == '/') {
			index[0]++;
			continue ;
		}
		if (isdigit(FEN[i])) {
			index[1] += FEN[i] - '0';
			if (index[1] == 8)
				index[1] = 0;
			continue ;
		}
		board[index[0]][index[1]] = FEN[i];
		index[1]++;
		if (index[1] == 8)
			index[1] = 0;
	}
}

void	initialiseEmptyBoard(char board[BOARD_H][BOARD_W]) {
	printf(SAVE_CURSOR_POS);
	for (size_t i = 0; i < BOARD_H; i++) {
		for (size_t j = 0; j < BOARD_W; j++) {
			board[i][j] = '.';
		}
	}
}
