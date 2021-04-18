#pragma once

#include <vector>

namespace sudokugame {

using std::vector;

/**
 * Provide a solution to a sudoku game.
 */
class SudokuSolver {
public:
  typedef vector<vector<size_t>> gameboard;
  
  /**
   * Constructor for this class, initialize a sudoku solver.
   * @param board a 2D vector storing the sudoku game board data
   */
  SudokuSolver(const gameboard& board);

  /**
   * Solves the sudoku game.
   * @return if the sudoku game is successfully solved
   */
  bool Solve();
  
  /**
   * Gets the solution (a complete board) of the sudoku game.
   * @return a complete sudoku game board
   */
  const gameboard& GetSolution() const; 

private:
  bool FillInNumbers();
  bool IsFull() const ;
  bool IsValid() const ;
  bool IsValidTile(size_t row, size_t col, size_t number) const;
  
  // A 2D vector storing the sudoku game board data 
  gameboard sudoku_board_;
  
  // Tiles on the board that need to be filled in
  std::vector<std::pair<size_t, size_t>> empty_tiles_;
  
  // The next tile to fill in some number.
  size_t tile_to_fill_;
};

} // namespace sudokugame
