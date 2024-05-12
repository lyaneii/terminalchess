/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: kwchu <kwchu@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/04/28 14:12:07 by kwchu         #+#    #+#                 */
/*   Updated: 2024/05/12 17:53:09 by kwchu         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
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
	char			c;
	t_boardInfo		info;
	int				exitCondition = 0;

	if (!setupGame(board, &original, &info))
		return 0;
	while (read(STDIN_FILENO, &c, 1) && c != 'q' && exitCondition == 0) {
		if (c == ' ')
			exitCondition = handleSelection(board, &info);
		else if (c == '\033')
			handleArrowKey(c, &info);
		displayBoard(board, &info);
	}
	exitCleanup(&info.moves, &original);
	return 0;
}
