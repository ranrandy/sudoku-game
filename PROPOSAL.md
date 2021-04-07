#CS 126 Final Project: Sudoku

`Introduction`

In general, I will implement a `Sudoku game GUI`. For more information about the game, please visit 
[wiki](https://en.wikipedia.org/wiki/Sudoku).

Specifically, I will use the C++ `Cinder` library to create the game from a starting
interface where the player can choose to begin a new game and choose difficulty of the game or quit, then to enter the 
Sudoku interface which will present a 9 x 9 Sudoku board with some numbers on it. Then the player
can use mouse to select certain square on the board and use keyboard (up, down) to choose the number to insert, delete
or replace.

I enjoyed playing Sudoku with my mom when I was young. And now my mom is also having fun with it with my little brother 
during their spare time. So, I hope to create an interesting Sudoku game with some unique features so that we can 
play together. Actually, I hope to turn this project to an app on iPhone if possible.

`Timeline:` 

Week 1:
- Generate correct numbers that conform to the rules of the game on a Sudoku board.
- Check if the newly inserted number contradicts to the state of the board.

Week 2:

- Implement the Sudoku board interface. 
- Implement using mouse and keyboard to insert and delete modifiable numbers on the board.
- Display message if obviously contradicted number is inserted to the board.

Week 3:

- Display the starting interface where the player can start a new game or quit.
- Display the winning message that will be sent to the screen and then let the player choose to start a new game or 
   quit.
   
`Extra Goals:`

1. Add a new feature "settings" to the starting interface where the player can change the background or 
   other appearances. 
2. Let the player to choose difficulties of the game and then generate different number of numbers on the board.
3. Add a rectangle board below the Sudoku board to show the remaining number of each number on the board.
4. Add a new feature "continue" to the starting interface where the player can choose to continue his / her last game.
   This will be implemented by storing game data to file when the game is quited and load the game from that file if 
   "continue" is selected.
5. Add a timer at some corner of the interface.
6. Add a "history" button to the starting interface where the player can see his / her game history. This history of 
   a list of games may contain the games' difficulty, duration, starting time, ending time, etc.
7. Implement offering some hints for the player.
8. Implement offering the best path to win after a game is finished. 
9. etc.