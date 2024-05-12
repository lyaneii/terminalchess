/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   terminalMode.h                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: kwchu <kwchu@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/08 13:19:19 by kwchu         #+#    #+#                 */
/*   Updated: 2024/05/12 17:58:16 by kwchu         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef TERMINALCHESS_TERMINALMODE_H
# define TERMINALCHESS_TERMINALMODE_H
# include <termios.h>

void	disableRawMode(struct termios *term);
void	enableRawMode(struct termios *original);
#endif