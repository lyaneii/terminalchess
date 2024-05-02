/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: kwchu <kwchu@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/04/28 14:12:07 by kwchu         #+#    #+#                 */
/*   Updated: 2024/05/02 13:23:39 by kwchu         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#define _XOPEN_SOURCE 500
#include <string.h>
#include <strings.h>
#include <stdlib.h>
#include <stdio.h>
#include "board.h"
#include "move.h"

void	__insertPiece(board_t *board, const char piece, const char *coords) {
	int	W = convertCoordToIndex(coords[0]);
	int	H = convertCoordToIndex(coords[1]);
	
	board->area[H][W] = piece;
}

static void	switchTurn(board_t *board) {
	board->turn = board->turn == 0 ? 1 : 0;
}

static int	resign(int turn, moveList_t **moveList) {
	if (turn == 0)
		addMove(moveList, "0-1");
	else
		addMove(moveList, "1-0");
	return -1;
}

static void	displayTurnPrompt(int turn) {
	printf("\033[0K");
	if (turn == 0)
		printf("White to move: ");
	else
		printf("Black to move: ");
}

static int	handleInput(board_t *board, char *input, moveList_t **moveList) {
	if (!strncmp(input, "pass", 5));
	else if (!strncmp(input, "resign", 7))
		return resign(board->turn, moveList);
	else if (executeMove(board, input) == 0)
		addMove(moveList, input);
	switchTurn(board);
	return 0;
}

int	main(void) {
	board_t 	board;
	moveList_t	*moveList = NULL;
	char		input[10];
	
	initBoard(&board, 0, 1);
	printf("\033[s");
	// __insertPiece(&board, 'n', "e6");
	// __insertPiece(&board, 'n', "e4");
	bzero(&input, 10);
	while (1) {
		drawBoard(board);
		displayTurnPrompt(board.turn);
		if (!fgets(input, 10, stdin))
			break ;
		input[strcspn(input, "\n")] = 0;
		if (handleInput(&board, input, &moveList) == -1)
			break ;
	}
	printMoveList(moveList);
	freeMoveList(moveList);
	return 0;
}
