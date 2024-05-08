/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   terminalMode.h                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: kwchu <kwchu@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/08 13:19:19 by kwchu         #+#    #+#                 */
/*   Updated: 2024/05/08 13:20:47 by kwchu         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef TERMINAL_CHESS_TERMINALMODE_H
# define TERMINAL_CHESS_TERMINALMODE_H
# include <termios.h>

void	disableRawMode(struct termios *term);
void	enableRawMode(struct termios *original);
#endif