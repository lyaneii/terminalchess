/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: kwchu <kwchu@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/04/28 14:12:07 by kwchu         #+#    #+#                 */
/*   Updated: 2024/04/28 21:06:44 by kwchu         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#define _XOPEN_SOURCE 500
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <readline/readline.h>
#define BOARD_W 10
#define BOARD_H 16
#define BOARD_START 3
#define BOARD_END 12
#define START_PIECES_W "rnbqkbnr"
#define START_PIECES_B "RNBQKBNR"
#define RED "\033[1;31m"
#define GREEN "\033[1;32m"
#define YELLOW "\033[1;33m"
#define BLUE "\033[1;34m"
#define WHITE "\033[1;37m"
#define RESET "\033[0m"

struct	board_s {
	char	area[BOARD_H][BOARD_W];
	char	*lastMove;
	int		turn;
};

void	createBorder(struct board_s *board) {
	for (int i = 0; i < BOARD_H; i++) {
		if (i == 0 || i == BOARD_H - 1) {
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

void	createStart(struct board_s *board) {
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

void	createCoords(struct board_s *board) {
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

void	initBoard(struct board_s *board, int turn) {
	createBorder(board);
	createCoords(board);
	createStart(board);
	board->lastMove = NULL;
	board->turn = turn;
}

void	drawPiece(char piece) {
	if (isalpha(piece)) {
		printf(WHITE);
		if (piece == 'P')
			printf("♙");
		else if (piece == 'R')
			printf("♖");
		else if (piece == 'N')
			printf("♘");
		else if (piece == 'B')
			printf("♗");
		else if (piece == 'K')
			printf("♔");
		else if (piece == 'Q')
			printf("♕");
		printf(RESET);
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
	}
	else
		printf("%c", piece);
	printf(RESET);
}

void	drawBoard(struct board_s board) {
	// printf("\033[u");
	for (int i = 0; i < BOARD_H; i++) {
		for (int j = 0; j < BOARD_W; j++) {
			if (i > BOARD_START && i < BOARD_END)
				drawPiece(board.area[i][j]);
			else
				printf("%c", board.area[i][j]);
			printf(" ");
		}
		printf("\n");
	}
}

int	convertCoordToIndex(char coord) {
	if (isalpha(coord)) {
		return coord - 'a' + 1;
	}
	else if (isdigit(coord)) {
		return 9 - (coord - '0') + BOARD_START;
	}
	return -1;
}

char	getPieceType(struct board_s *board, const int *coords) {
	return board->area[coords[1]][coords[0]];
}

int	startPawnMove(struct board_s *board, const int *coords) {
	if (board->turn == 0 && coords[1] == convertCoordToIndex('4')) {
		if (board->area[coords[1] + 1][coords[0]] == 'p' || \
			board->area[coords[1] + 2][coords[0]] == 'p')
			return 0;
	}
	else if (board->turn == 1 && coords[1] == convertCoordToIndex('5')) {
		if (board->area[coords[1] - 1][coords[0]] == 'P' || \
			board->area[coords[1] - 2][coords[0]] == 'P')
			return 0;
	}
	return -1;
}

int	checkTarget(struct board_s *board, const char targetPiece, const int *coords, const int column, int capture) {
	int	captureDirection = 0;
	
	if (targetPiece != '.')
		captureDirection = islower(targetPiece) ? -1 : 1;
	if (board->turn == 0 && captureDirection == -1)
		return -1;
	if (board->turn == 1 && captureDirection == 1)
		return -1;
	if (capture == 1 && targetPiece == '.')
		return -1;
	if (capture == 0 && targetPiece != '.')
		return -1;
	if (capture == 1) {
		if (captureDirection == 1 && board->area[coords[1] + captureDirection][column] != 'p')
			return -1;
		if (captureDirection == -1 && board->area[coords[1] + captureDirection][column] != 'P')
			return -1;
	}
	if (capture == 0) {
		if (startPawnMove(board, coords) == 0)
			return 0;
		if (board->turn == 0 && board->area[coords[1] + 1][coords[0]] != 'p')
			return -1;
		if (board->turn == 1 && board->area[coords[1] - 1][coords[0]] != 'P')
			return -1;
	}
	return 0;
}

int	validatePawnMove(struct board_s *board, const char *target, int column, int capture) {
	int 	targetCoords[2];
	char	targetPiece;

	if (capture == 1 && strlen(target) != 2)
		return -1;
	if (capture == 1) {
		targetCoords[0] = convertCoordToIndex(target[0]);
		targetCoords[1] = convertCoordToIndex(target[1]);
	}
	else {
		targetCoords[0] = column;
		targetCoords[1] = convertCoordToIndex(target[0]);
	}
	targetPiece = getPieceType(board, targetCoords);
	return checkTarget(board, targetPiece, targetCoords, column, capture);
}

int	pawnMove(struct board_s *board, const char *move) {
	int	column;
	int	capture = 0;

	column = convertCoordToIndex(move[0]);
	if (move[1] == 'x')
		capture = 1;
	return validatePawnMove(board, move + capture + 1, column, capture);
}

int	checkMove(struct board_s *board, const char *move) {
	if (!strchr("abcdefghNBQRK", move[0]))
		return -1;
	if (strchr("abcdefgh", move[0]))
		return pawnMove(board, move);
	// if (move[0] == 'N')
	// 	return knightMove(board, move);
	return 0;
}

int executeMove(struct board_s *board, const char *move) {
	printf("move: %s\n", move);
	if (checkMove(board, move) == -1) {
		printf("%sinvalid move%s\n", RED, RESET);
		return -1;
	}
	printf("%svalid move%s\n", GREEN, RESET);
	
	return 0;
}

void	__insertPiece(struct board_s *board, const char piece, const char *coords) {
	int	W = convertCoordToIndex(coords[0]);
	int	H = convertCoordToIndex(coords[1]);
	
	board->area[H][W] = piece;
}

int	main(void) {
	struct board_s board;
	char	*input;
	char	move[3];
	int		turn = 0;
	
	initBoard(&board, 0);
	// printf("\033[s");
	__insertPiece(&board, 'p', "e4");
	__insertPiece(&board, 'P', "f5");
	while (1) {
		drawBoard(board);
		if (turn == 0)
			input = readline("White to move: ");
		else
			input = readline("Black to move: ");
		if (!input)
			break ;
		if (!strncmp(move, "resign", 7))
			break ;
		if (executeMove(&board, input) == 0) {
			board.lastMove = strdup(input);
			if (!board.lastMove) {
				perror("lastMove malloc fail: ");
				break ;
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
