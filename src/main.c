/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: kwchu <kwchu@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/04/28 14:12:07 by kwchu         #+#    #+#                 */
/*   Updated: 2024/05/07 22:58:55 by kwchu         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <termios.h>
#include <unistd.h>

void	disableRawMode(struct termios *term) {
	tcsetattr(STDIN_FILENO, TCSAFLUSH, term);
}

void	enableRawMode(struct termios *original) {
	struct termios term;

	tcgetattr(STDIN_FILENO, original);
	term = *original;
	term.c_lflag &= ~(ECHO | ICANON);
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &term);
}

int	main(void) {
	struct termios original;
	char	c;

	enableRawMode(&original);
	while (read(STDIN_FILENO, &c, 1) && c != 'q');
	disableRawMode(&original);
	return 0;
}
