/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   moveList.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: kwchu <kwchu@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/04/30 18:06:21 by kwchu         #+#    #+#                 */
/*   Updated: 2024/05/02 16:37:43 by kwchu         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#define _XOPEN_SOURCE 500
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "move.h"

void	printMoveList(moveList_t *moveList) {
	int	counter = 1;

	printf("\033[0K");
	if (!moveList)
		return ;
	printf("\n[Move Sheet]\n");
	while (moveList) {
		if (moveList->turn == 0)
			printf("%d.  %s\t\t", counter++, moveList->move);
		else
			printf("%s", moveList->move);
		if (moveList->turn == 1 || strchr(moveList->move, '0'))
			printf("\n");
		moveList = moveList->next;
	}
}

moveList_t	*newMove(char *move, int turn) {
	moveList_t	*new;

	new = malloc(sizeof(moveList_t));
	if (!new)
		return NULL;
	new->move = move;
	new->turn = turn;
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

void	addMove(moveList_t **head, const char *input, int turn, int check) {
	moveList_t	*move;
	char		*dup;

	if (check != 0)
		dup = malloc((strlen(input) + 2) * sizeof(char));
	else
		dup = malloc((strlen(input) + 1) * sizeof(char));
	if (!dup)
		return perror("dup malloc fail: ");
	strcpy(dup, input);
	if (check == 1)
		strcat(dup, "+");
	else if (check == 2)
		strcat(dup, "#");
	move = newMove(dup, turn);
	if (!move)
		return (perror("newMove malloc fail: "), free(dup));
	if (!*head)
		*head = move;
	else
		lastMove(*head)->next = move;
}

void	freeMoveList(moveList_t *head) {
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
