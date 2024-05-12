/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   initialise.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: kwchu <kwchu@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/12 02:11:17 by kwchu         #+#    #+#                 */
/*   Updated: 2024/05/12 14:12:55 by kwchu         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdio.h>
#include <ctype.h>
#include "moves.h"
#include "initialise.h"

void	initialiseHighlight(t_boardInfo *info) {
	info->cursor[0] = 0;
	info->cursor[1] = 0;
	info->selectedPiece[0] = -1;
	info->selectedPiece[1] = 0;
	info->lastMove[0][0] = -1;
	info->lastMove[0][1] = 0;
	info->lastMove[1][0] = 0;
	info->lastMove[1][1] = 0;
	info->castleRights[0][0] = 0;
	info->castleRights[0][1] = 0;
	info->castleRights[1][0] = 0;
	info->castleRights[1][1] = 0;
	info->turn = 1;
	info->moves = NULL;
}

void	loadFEN(char board[BOARD_H][BOARD_W], const char *FEN, t_boardInfo *info) {
	int		index[2] = {0, 0};
	size_t	i;

	for (i = 0; FEN[i] && FEN[i] != ' '; i++) {
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
	while (FEN[i]) {
		if (FEN[i] == 'b')
			info->turn = 0;
		if (FEN[i] == 'K')
			info->castleRights[0][0] = 1;
		if (FEN[i] == 'Q')
			info->castleRights[0][1] = 1;
		if (FEN[i] == 'k')
			info->castleRights[1][0] = 1;
		if (FEN[i] == 'q')
			info->castleRights[1][1] = 1;
		i++;
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
