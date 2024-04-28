/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   drawPiece.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: kwchu <kwchu@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/04/28 22:35:31 by kwchu         #+#    #+#                 */
/*   Updated: 2024/04/28 22:45:57 by kwchu         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include "colours.h"

static void	drawWhitePiece(char piece) {
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

static void	drawBlackPiece(char piece) {
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
}

int	isPiece(char c) {
	if (strchr("prnbkq", tolower(c)) != NULL)
		return 1;
	return 0;
}

void	drawPiece(char piece) {
	if (islower(piece))
		drawWhitePiece(piece);
	else
		drawBlackPiece(piece);
}
