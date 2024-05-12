/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   defines.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: kwchu <kwchu@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/04/28 21:34:04 by kwchu         #+#    #+#                 */
/*   Updated: 2024/05/12 16:59:07 by kwchu         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef TERMINALCHESS_DEFINES_H
# define TERMINALCHESS_DEFINES_H

# define RED "\033[1;31m"
# define GREEN "\033[1;32m"
# define YELLOW "\033[1;33m"
# define BLUE "\033[1;34m"
# define WHITE "\033[1;37m"
# define RESET "\033[0m"

# define START_RANK_W 6
# define START_RANK_B 1
# define EN_PASSANT_RANK_W 3
# define EN_PASSANT_RANK_B 4

# define SAVE_CURSOR_POS "\033[s"
# define LOAD_CURSOR_POS "\033[u"
# define CURSOR_DOWN_2 "\033[2E"

# define BOARD_W 8
# define BOARD_H 8
# define FILL "◻"
# define HIGHLIGHT "❏"
# define MOVES "◼"
# define LAST_MOVE "⛶"
// ◻⛶
#endif