/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executeMove.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: kwchu <kwchu@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/04/28 23:00:14 by kwchu         #+#    #+#                 */
/*   Updated: 2024/04/28 23:41:07 by kwchu         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdio.h>
#include "move.h"
#include "colours.h"

static int	determineMove(board_t *board, const char *move) {
	if (!strchr("abcdefghNBQRK", move[0]))
		return -1;
	if (strchr("abcdefgh", move[0]))
		return pawnMove(board, move);
	// if (move[0] == 'N')
	// 	return knightMove(board, move);
	return 0;
}

int executeMove(board_t *board, const char *move) {
	printf("move: %s\n", move);
	if (determineMove(board, move) == -1) {
		printf("%sinvalid move%s\n", RED, RESET);
		return -1;
	}
	printf("%svalid move%s\n", GREEN, RESET);
	
	return 0;
}
