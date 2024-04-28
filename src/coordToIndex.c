/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   coordToIndex.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: kwchu <kwchu@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/04/28 22:56:08 by kwchu         #+#    #+#                 */
/*   Updated: 2024/04/28 22:58:16 by kwchu         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "board.h"
#include <ctype.h>

int	convertCoordToIndex(char coord) {
	if (isalpha(coord))
		return coord - 'a' + 1;
	else if (isdigit(coord))
		return 9 - (coord - '0') + BOARD_START;
	return -1;
}
