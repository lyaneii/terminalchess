/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: kwchu <kwchu@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/04/28 14:12:07 by kwchu         #+#    #+#                 */
/*   Updated: 2024/04/30 00:35:19 by kwchu         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#define _XOPEN_SOURCE 500
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <readline/readline.h>
#include "board.h"
#include "move.h"

void	__insertPiece(board_t *board, const char piece, const char *coords) {
	int	W = convertCoordToIndex(coords[0]);
	int	H = convertCoordToIndex(coords[1]);
	
	board->area[H][W] = piece;
}

int	main(void) {
	board_t board;
	char	*input;
	int		turn = 0;
	
	initBoard(&board, 0, 1);
	// printf("\033[s");
	// __insertPiece(&board, 'n', "e6");
	// __insertPiece(&board, 'n', "e4");
	while (1) {
		drawBoard(board);
		if (turn == 0)
			input = readline("White to move: ");
		else
			input = readline("Black to move: ");
		if (!input)
			break ;
		if (!strncmp(input, "resign", 7))
			break ;
		if (!strncmp(input, "pass", 5)) {
			turn = turn == 1 ? 0 : 1;
			board.turn = turn;
			free(input);
			continue ;
		}
		if (executeMove(&board, input) == 0) {
			if (board.lastMove != NULL)
				free(board.lastMove);
			board.lastMove = strdup(input);
			if (!board.lastMove) {
				perror("lastMove malloc fail: ");
				free(input);
				return 1;
			}
			turn = turn == 1 ? 0 : 1;
			board.turn = turn;
		}
		free(input);
	}
	free(input);
	if (board.lastMove != NULL)
		free(board.lastMove);
	return 0;
}
