/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: kwchu <kwchu@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/04/28 14:12:07 by kwchu         #+#    #+#                 */
/*   Updated: 2024/04/30 17:43:28 by kwchu         ########   odam.nl         */
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

void	printMoveList(moveList_t *moveList) {
	int	counter = 1;
	int	turn = 0;

	printf("\033[0K");
	if (!moveList)
		return ;
	printf("[Move Sheet]\n");
	while (moveList) {
		if (turn == 0)
			printf("%d. ", counter++);
		printf("%s", moveList->move);
		turn++;
		if (turn == 1)
			printf("\t");
		if (turn > 1 || strchr(moveList->move, '0')) {
			printf("\n");
			turn = 0;
		}
		moveList = moveList->next;
	}
}

moveList_t	*newMove(char *move) {
	moveList_t	*new;

	new = malloc(sizeof(moveList_t));
	if (!new)
		return NULL;
	new->move = move;
	new->next = NULL;
	return new;
}

moveList_t	*lastMove(moveList_t *head) {
	if (!head)
		return NULL;
	while (head->next)
		head = head->next;
	return head;
}

void	addMove(moveList_t **head, const char *input) {
	moveList_t	*move;
	char		*dup;

	dup = strdup(input);
	if (!dup)
		return perror("dup malloc fail: ");
	move = newMove(dup);
	if (!move)
		return (perror("newMove malloc fail: "), free(dup));
	if (!*head)
		*head = move;
	else
		lastMove(*head)->next = move;
}

static void	switchTurn(board_t *board) {
	board->turn = board->turn == 0 ? 1 : 0;
}

static void	freeMoveList(moveList_t *head) {
	moveList_t	*tmp;
	
	if (!head)
		return ;
	while (head) {
		tmp = head;
		head = head->next;
		free(tmp->move);
		free(tmp);
	}
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
		printf("\033[0K");
		if (board.turn == 0)
			printf("White to move: ");
		else
			printf("Black to move: ");
		if (!fgets(input, 10, stdin))
			break ;
		input[strcspn(input, "\n")] = 0;
		if (!strncmp(input, "resign", 7)) {
			if (board.turn == 0)
				addMove(&moveList, "0-1");
			else
				addMove(&moveList, "1-0");
			break ;
		}
		if (!strncmp(input, "pass", 5)) {
			switchTurn(&board);
		} else if (executeMove(&board, input) == 0) {
			addMove(&moveList, input);
			switchTurn(&board);
		}
		bzero(&input, 10);
	}
	printMoveList(moveList);
	freeMoveList(moveList);
	return 0;
}
