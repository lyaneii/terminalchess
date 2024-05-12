# TerminalChess
TerminalChess is a small hobby project where you are able to play Chess from a Linux terminal.

# Features
TerminalChess features the game of chess including all of its rules: piece movement, checks, checkmate, etc..\
It also includes the special rules:
- 2-square pawn push at start
- En passant
- Castling
- Pawn promotion

The board is setup with the default chess position using the FEN format. It can be adjusted in `src/main.c` if you would like to load a specific position, in the future I will include a way to input your own custom position in a more friendly way.\
As of now can only be played locally against another person on the same computer.

# How to play
## Build
To play TerminalChess you need to build the executable.\
Building is done by simply running make in the root directory:
```bash
git clone https://github.com/lyaneii/terminalchess.git terminalchess
cd terminalchess
make
```
## Run
To start the game you simply run the program without any arguments:
```bash
./terminalchess
```
## Scaling
Since the game relies on the unicode character set of the chess pieces, it is advised to change the font size of the terminal or adjust the zoom level of the terminal with `ctrl +` and `ctrl -` *(or other keyboard shortcuts)*.

# Controls
Your `cursor` is highlighted in `red`, by default it is controlled using the `arrow keys (←↑↓→)` and in case your keyboard does not have them, you can use `WASD` to control the cursor.\
To `select a piece or move`, you can use `Spacebar`.\
To `deselect a piece`, you can `select an empty square` or `select the highlighted piece` again.\
A `selected piece` and their `available moves` are highlighted in `yellow`.\
`Selecting a move` highlighted in `yellow` will `perform the move`.\
The `last move` is highlighted in `green`, along with a rounded square indicating where it was moved from.

## Editing keybinds
As of now the only way to change keybinds is to go into the code and change the variables in `include/defines.h`, here is an example of the original:
```c
...
# define CHAR_CONTROLS "wasd" /* w = up | a = left | s = down | d = right */
# define CHAR_SELECT ' ' /* ' ' is the >spacebar< key */
...
```
Here is an example of an edited version of the keybinds:
```c
...
# define CHAR_CONTROLS "ijkl" /* i = up | j = left | k = down | l = right */
# define CHAR_SELECT '\n' /* '\n' is the >enter< key */
...
```

# To-do list
Features are somewhat listed in order of priority.
- [x] A working game of chess!
- [ ] Add a chessbot to play against. ~~*(if you have no friends)*~~
- [ ] Add a menu to do various things before playing, e.g. loading a custom chess position.
- [ ] Add a way to customise keybinds/controls for selecting pieces on the board.
- [ ] Ability to export the game to a PGN format.
- [ ] Add support for last 2 arguments of FEN format.
- [ ] Add images/GIFs to README.
- [ ] Add support for Powershell.
- [ ] More...
