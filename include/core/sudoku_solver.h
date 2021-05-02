#pragma once

#include <vector>

namespace sudokugame {

using std::vector;

/**
 * Provides a solution to a sudoku game. If one sudoku game has multiple 
 * solutions, this class can only provide one of them.
 */
class SudokuSolver {
public:
  typedef vector<vector<size_t>> gameboard;
  
  /**
   * Constructs a sudoku solver.
   * @param board a 2D vector storing the sudoku game board data (numbers)
   */
  SudokuSolver(const gameboard& board);

  /**
   * Solves the sudoku game.
   * @return true if the sudoku game is successfully solved
   */
  bool Solve();
  
  /**
   * Gets one solution (a complete board) of the sudoku game.
   * @return a complete sudoku game board
   */
  const gameboard& GetSolution() const; 

private:
  /**
   * Fill in the whole sudoku board with numbers.
   * @return true if the board has been successfully filled in
   */
  bool FillInNumbers();
  
  /**
   * Checks if the sudoku board is full.
   * @return true if the sudoku board is full
   */
  bool IsFull() const;
  
  /**
   * Checks if the sudoku board is valid.
   * @return true if the sudoku board is valid
   */
  bool IsValid() const;
  
  /**
   * Checks if one tile is valid, namely if one tile conforms to the rule.
   * @param row row index
   * @param col column index
   * @param number the number in the tile
   * @return true if this tile is valid
   */
  bool IsValidTile(size_t row, size_t col, size_t number) const;
  
  // A 2D vector storing the sudoku game board data 
  gameboard sudoku_board_;
  
  // Empty tiles on the board that need to be filled in
  std::vector<std::pair<size_t, size_t>> empty_tiles_;
  
  // The next tile to fill in some number.
  size_t tile_to_fill_;
};

} // namespace sudokugame
