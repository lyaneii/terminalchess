/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   moveList.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: kwchu <kwchu@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/04/30 18:06:21 by kwchu         #+#    #+#                 */
/*   Updated: 2024/04/30 20:02:45 by kwchu         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "move.h"

void	printMoveList(moveList_t *moveList) {
	int	counter = 1;
	int	turn = 0;

	printf("\033[0K");
	if (!moveList)
		return ;
	printf("\n[Move Sheet]\n");
	while (moveList) {
		if (turn == 0)
			printf("%d. ", counter++);
		printf("%s", moveList->move);
		turn++;
		if (turn == 1)
			printf("\t ");
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
