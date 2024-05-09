/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   defines.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: kwchu <kwchu@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/04/28 21:34:04 by kwchu         #+#    #+#                 */
/*   Updated: 2024/05/09 14:50:28 by kwchu         ########   odam.nl         */
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

# define SAVE_CURSOR_POS "\033[s"
# define LOAD_CURSOR_POS "\033[u"

# define BOARD_W 8
# define BOARD_H 8
# define FILL "◻"
# define HIGHLIGHT "❏"
# define MOVES "◼"
# define LAST_MOVE "⛶"
// ◻⛶
#endif