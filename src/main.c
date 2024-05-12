/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: kwchu <kwchu@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/04/28 14:12:07 by kwchu         #+#    #+#                 */
/*   Updated: 2024/05/12 23:15:43 by kwchu         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include "moves.h"
#include "defines.h"
#include "terminalMode.h"
#include "controls.h"
#include "displayBoard.h"
#include "initialise.h"

static int	setupGame(char board[BOARD_H][BOARD_W], struct termios *term, t_boardInfo *info) {
	initialiseEmptyBoard(board);
	initialiseHighlight(info);
	loadFEN(board, "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1", info);
	displayBoard(board, info);
	enableRawMode(term);
	if (isCheckmate(board, info)) {
		disableRawMode(term);
		return 0;
	}
	return 1;
}

static void exitCleanup(t_moves **moves, struct termios *term) {
	printf(CURSOR_DOWN_2);
	cleanupMoves(moves);
	disableRawMode(term);
}

int	main(void) {
	char			board[BOARD_H][BOARD_W];
	struct termios	original;
	char			input;
	t_boardInfo		info;
	int				exitCondition = 0;

	if (!setupGame(board, &original, &info))
		return 0;
	while (read(STDIN_FILENO, &input, 1) && input != 'q' && exitCondition == 0) {
		if (input == CHAR_SELECT)
			exitCondition = handleSelection(board, &info);
		else if (strchr(CHAR_CONTROLS, input))
			handleCharControls(input, &info);
		else if (input == '\033')
			handleArrowKey(input, &info);
		displayBoard(board, &info);
	}
	exitCleanup(&info.moves, &original);
	return 0;
}
