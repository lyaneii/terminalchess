/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   movesList.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: kwchu <kwchu@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/12 01:35:14 by kwchu         #+#    #+#                 */
/*   Updated: 2024/05/12 01:39:07 by kwchu         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "moves.h"

t_moves	*newMove(int target[2], int specialMove) {
	t_moves	*move;

	move = malloc(sizeof(t_moves));
	if (!move)
		return NULL;
	move->target[0] = target[0];
	move->target[1] = target[1];
	move->specialMove = specialMove;
	move->next = NULL;
	return move;
}

void	addMove(t_moves **head, t_moves *move) {
	if (!move)
		return ;
	if (!*head)
		*head = move;
	else {
		move->next = *head;
		*head = move;
	}
}

void	cleanupMoves(t_moves **moves) {
	t_moves	*tmp;

	while (*moves) {
		tmp = *moves;
		*moves = (*moves)->next;
		free(tmp);
	}
	*moves = NULL;
}
