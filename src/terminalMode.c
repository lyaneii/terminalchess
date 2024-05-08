/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   terminalMode.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: kwchu <kwchu@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/08 13:18:42 by kwchu         #+#    #+#                 */
/*   Updated: 2024/05/08 13:19:05 by kwchu         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <termios.h>
#include <unistd.h>

void	disableRawMode(struct termios *term) {
	tcsetattr(STDIN_FILENO, TCSAFLUSH, term);
}

void	enableRawMode(struct termios *original) {
	struct termios	term;

	tcgetattr(STDIN_FILENO, original);
	term = *original;
	term.c_lflag &= ~(ECHO | ICANON);
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &term);
}
