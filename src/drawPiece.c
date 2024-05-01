/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   drawPiece.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: kwchu <kwchu@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/04/28 22:35:31 by kwchu         #+#    #+#                 */
/*   Updated: 2024/05/01 13:43:18 by kwchu         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "board.h"
#include "colours.h"

static void	drawPieceSet1(char piece, const char *colour) {
	if (colour)
		printf("%s", colour);
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

// static void	drawPieceSet2(char piece, const char *colour) {
// 	if (colour)
// 		printf("%s", colour);
// 	if (piece == 'P')
// 		printf("♙");
// 	else if (piece == 'R')
// 		printf("♖");
// 	else if (piece == 'N')
// 		printf("♘");
// 	else if (piece == 'B')
// 		printf("♗");
// 	else if (piece == 'K')
// 		printf("♔");
// 	else if (piece == 'Q')
// 		printf("♕");
// }

int	isPiece(char c) {
	if (strchr("prnbkq.", tolower(c)) != NULL)
		return 1;
	return 0;
}

void	drawPiece(char piece, int row, int column) {
	if (piece == '.') {
		if (abs(row - column) % 2 == 0)
			printf(BOARD_FILL);
		else
			printf(BOARD_FILL);
	}
	else if (islower(piece))
		drawPieceSet1(tolower(piece), NULL);
	else
		drawPieceSet1(tolower(piece), WHITE);
	printf(RESET);
}
