/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: kwchu <kwchu@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/04/28 14:12:07 by kwchu         #+#    #+#                 */
/*   Updated: 2024/05/08 01:37:02 by kwchu         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "defines.h"
#include <termios.h>
#include <unistd.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

void	displayPieceSet(char piece, int highlight) {
	if (highlight)
		printf(RED);
	else if (islower(piece))
		printf(WHITE);
	piece = tolower(piece);
	if (piece == 'p')
		printf("♟︎");
	else if (piece == 'r')
		printf("♜");
	else if (piece == 'n')
		printf("♞");
	else if (piece == 'b')
		printf("♝");
	else if (piece == 'k')
		printf("♚");
	else if (piece == 'q')
		printf("♛");
	else if (piece == '.') {
		if (highlight)
			printf(HIGHLIGHT);
		else
			printf(FILL);
	}
	printf(RESET);
}

void	displayBoard(const char board[BOARD_H][BOARD_W], int cursor[2]) {
	printf(LOAD_CURSOR_POS);
	for (int i = 0; i < BOARD_H; i++) {
		for (int j = 0; j < BOARD_W; j++) {
			if (i == cursor[0] && j == cursor[1])
				displayPieceSet(board[i][j], 1);
			else
				displayPieceSet(board[i][j], 0);
			printf(" ");
		}
		printf("\n");
	}
}

void	disableRawMode(struct termios *term) {
	tcsetattr(STDIN_FILENO, TCSAFLUSH, term);
}

void	enableRawMode(struct termios *original) {
	struct termios	term;

	tcgetattr(STDIN_FILENO, original);
	term = *original;
	term.c_lflag &= ~(ECHO | ICANON);
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &term);
}

int	convertCoordinateToIndex(char coordinate) {
	if (strchr("abcdefgh", coordinate))
		return coordinate - 'a' + 1;
	else if (strchr("12345678", coordinate))
		return coordinate - '0' - 1;
	return -1;
}

void	putPiece(char board[BOARD_H][BOARD_W], const char piece, const char coordinate[2]) {
	int	index[2];

	index[0] = convertCoordinateToIndex(coordinate[0]);
	index[1] = convertCoordinateToIndex(coordinate[1]);
	if (index[0] == -1 || index[1] == -1)
		return ;
	board[index[0]][index[1]] = piece;
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

void	initBoard(char board[BOARD_H][BOARD_W]) {
	printf(SAVE_CURSOR_POS);
	for (size_t i = 0; i < BOARD_H; i++) {
		for (size_t j = 0; j < BOARD_W; j++) {
			board[i][j] = '.';
		}
	}
}

void	handleArrowKey(char c, int cursor[2]) {
	if (read(STDIN_FILENO, &c, 1) && c == '[') {
		read(STDIN_FILENO, &c, 1);
		if (c == 'A')
			cursor[0] - 1 >= 0 ? cursor[0]-- : 0;
		else if (c == 'B')
			cursor[0] + 1 < BOARD_H ? cursor[0]++ : BOARD_H;
		else if (c == 'C')
			cursor[1] + 1 < BOARD_W ? cursor[1]++ : BOARD_H;
		else if (c == 'D')
			cursor[1] - 1 >= 0 ? cursor[1]-- : 0;
	}
}

int	main(void) {
	char			board[BOARD_H][BOARD_W];
	struct termios	original;
	char			c;
	int				cursor[2] = {0, 0};

	initBoard(board);
	loadFEN(board, "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR");
	displayBoard(board, cursor);
	enableRawMode(&original);
	while (read(STDIN_FILENO, &c, 1) && c != 'q') {
		if (c == '\033')
			handleArrowKey(c, cursor);
		displayBoard(board, cursor);
	}
	disableRawMode(&original);
	return 0;
}
